// GL Library
#include <GL/glew.h>
#include <GL/glfw.h>

// Standard Library
#include <cassert>
#include <iostream>
#include <stdexcept>

// Backlash Library
#include "../Util/util.h"
#include "GraphicsManager.h"
#include "Program.h"

// Global static pointer used to ensure my singleton
backlash::GraphicsManager* backlash::GraphicsManager::mInstance;

namespace backlash {
    GraphicsManager* GraphicsManager::GetInstance() {
        if (!mInstance) {
            mInstance = new GraphicsManager;
        }
        return mInstance;
    }

    GraphicsManager::GraphicsManager() : mActiveShader(nullptr) {}

    void GraphicsManager::LoadShaders() {
        std::vector<Shader> shaders;

        shaders.push_back(Shader::ShaderFromFile(utility::ResourcePath("vertex-shader.vert"), GL_VERTEX_SHADER));

        shaders.push_back(Shader::ShaderFromFile(utility::ResourcePath("fragment-shader.frag"), GL_FRAGMENT_SHADER));

        mShaders.push_back(new Program(shaders));
    }

    void GraphicsManager::AddDrawComponent(std::shared_ptr<DrawComponent> comp) {
        if (!comp)
            throw std::runtime_error("Draw Component is a null pointer when you tried to add it to the Graphics Manager");

        mDrawComponents.push_back(std::weak_ptr<DrawComponent>(comp));
    }

    void GraphicsManager::AddLightComponent(std::shared_ptr<LightComponent> comp) {
        if (!comp)
            throw std::runtime_error("Light Component is a null pointer when you tried to add it to the Graphics Manager");

        mLightComponents.push_back(std::weak_ptr<LightComponent>(comp));
    }

    void GraphicsManager::AddCameraComponent(std::shared_ptr<CameraComponent> comp) {
        if (!comp)
            throw std::runtime_error("Camera Component is a null pointer when you tried to add it to the Graphics Manager");
        mCameraComponent = comp;
    }

    void GraphicsManager::AttachShaderToDrawComponent(DrawComponent* comp, int id) {
        if (id >= mShaders.size() || id < 0)
            throw std::runtime_error("Invalid Shader ID to attach to the draw component.");
        comp->SetShader(mShaders.at(id));
    }

    void GraphicsManager::AttachMeshToDrawComponent(DrawComponent* comp, int id) {
        if (mMeshes->count(id) <= 0) {
            std::cerr << "Supposed Mesh ID: " << id << std::endl;
            throw std::runtime_error("Mesh does not exist in mMeshes to attach to the draw component.");
        }

        std::shared_ptr<Mesh> mesh(mMeshes->at(id));
        comp->SetMesh(mesh);
    }

    void GraphicsManager::SetTextureSharedPointer(
        std::shared_ptr<std::map<std::string, Texture*>>& textures)
    {
        mTextures = textures;
    }

    void GraphicsManager::SetMeshSharedPointer(
        std::shared_ptr<std::map<int, Mesh*>>& meshes) 
    {
        mMeshes = meshes;
    }

    void GraphicsManager::Render() {
        // Clearing everything
        glClearColor(0,0,0,1); // black.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        mActiveShader = nullptr;

        for (auto it = mDrawComponents.begin(); it != mDrawComponents.end(); ++it) {
            if ((*it).expired()) {
                it = mDrawComponents.erase(it);
                it--;
                continue;
            }

            auto drawComp = (*it).lock();
            if (!drawComp)
                std::runtime_error("Draw Component couldn't be locked when trying to render it.");

            Program* curShader = drawComp->GetShader();
            if (mActiveShader != curShader) {
                mActiveShader = curShader;
            }

            if (!mActiveShader->IsInUse()) {
                // make the shader active 
                mActiveShader->Use();

                // Render the Camera Component
                auto cameraComp = mCameraComponent.lock();
                if (!cameraComp)
                    std::runtime_error("Camera Component couldn't be locked when trying to render it.");
                cameraComp->Render(mActiveShader);

                // Render Light Components
                for (auto it : mLightComponents) {
                    if (auto lightComp = (it).lock()) {
                        lightComp->Render(mActiveShader);
                    } else {
                        std::runtime_error("Light Component couldn't be locked when trying to render it.");
                    }

                }
            }
            std::string materialName = drawComp->GetMaterialName();
            mTextures->at(materialName)->BindTexture(mActiveShader);

            drawComp->Render(mActiveShader);

            mTextures->at(materialName)->UnbindTexture();
        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        mActiveShader->Stop();
        
        // swap the display buffers (displays what was just drawn)
        glfwSwapBuffers();
    }
}
