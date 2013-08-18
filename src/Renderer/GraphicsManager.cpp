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

// TEMP
#include "Bitmap.h"

// Global static pointer used to ensure my singleton
backlash::GraphicsManager* backlash::GraphicsManager::mInstance;

namespace backlash {
    void GraphicsManager::LoadCube() {
        drawType = GL_TRIANGLES;
        drawStart = 0;
        drawCount = 6*2*3;
        transform = glm::mat4();

        Bitmap bmp = Bitmap::BitmapFromFile(utility::ResourcePath("wooden-crate.jpg"));
        bmp.FlipVertically();
        crateTexture = new Texture(bmp, "wooden-crate.jpg");
        crateTexture->SetShininess(80.0);
        crateTexture->SetSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        glGenBuffers(1, &gVBO);
        glGenVertexArrays(1, &gVAO);

        // bind the VAO
        glBindVertexArray(gVAO);

        // bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, gVBO);

        // Make a cube out of triangles (two triangles per side)
        GLfloat vertexData[] = {
            //  X     Y     Z       U     V          Normal
            // bottom
            -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
             1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
            -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
             1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
             1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
            -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,

            // top
            -1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
             1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
             1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
             1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f,

            // front
            -1.0f,-1.0f, 1.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
             1.0f,-1.0f, 1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
             1.0f,-1.0f, 1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
             1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f,

            // back
            -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
            -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
             1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
             1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
            -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
             1.0f, 1.0f,-1.0f,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f,

            // left
            -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
            -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
            -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
            -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
            -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
            -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,

            // right
             1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
             1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
             1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
             1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
             1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
             1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   1.0f, 0.0f, 0.0f
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        // connect the xyz to the "vert" attribute of the vertex shader
        glEnableVertexAttribArray(mShaders.at(0)->Attrib("vert"));
        glVertexAttribPointer(mShaders.at(0)->Attrib("vert"), 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), NULL);

        // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
        glEnableVertexAttribArray(mShaders.at(0)->Attrib("vertTexCoord"));
        glVertexAttribPointer(mShaders.at(0)->Attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  8*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

        // connect the normal to the "vertNormal" attribute of the vertex shader
        glEnableVertexAttribArray(mShaders.at(0)->Attrib("vertNormal"));
        glVertexAttribPointer(mShaders.at(0)->Attrib("vertNormal"), 3, GL_FLOAT, GL_TRUE,  8*sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));

        // unbind the VAO
        glBindVertexArray(0);
    }









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
        mShaders.at(0)->Use();
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
        comp->SetMesh(mMeshes->at(id));
    }

    void GraphicsManager::SetTextureSharedPointer(
        std::shared_ptr<std::map<std::string, Texture*>>& textures)
    {
        mTextures = textures;
    }

    void GraphicsManager::SetMeshSharedPointer(
        std::shared_ptr<std::map<int, std::shared_ptr<Mesh>>>& meshes) 
    {
        mMeshes = meshes;
    }

    void GraphicsManager::Render() {
        // Clearing everything
        // std::cout << "Rendering the scene!" << std::endl;

        glClearColor(0.0f,0.0f,0.0f,0.0f); // black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!mShaders.at(0)->IsInUse()) {
            mShaders.at(0)->Use();
        }

        // Render the Camera Component

        auto cameraComp = mCameraComponent.lock();
        if (!cameraComp)
            throw std::runtime_error("Camera Component couldn't be locked when trying to render it.");
        
        if (!cameraComp->Render(mShaders.at(0)))
            throw std::runtime_error("The Camera Component wasn't Rendered properly.");

        // Render Light Components
        for (auto it : mLightComponents) {
            if (auto lightComp = (it).lock()) {
                if (!lightComp->Render(mShaders.at(0)))
                    throw std::runtime_error("The Light Component wasn't Rendered properly.");
            } else {
                throw std::runtime_error("Light Component couldn't be locked when trying to render it.");
            }
        }


        // TEMP
        mShaders.at(0)->SetUniform("model", transform);

        glBindBuffer(GL_ARRAY_BUFFER, gVBO);

        crateTexture->BindTexture(mShaders.at(0));

        glBindVertexArray(gVAO);
        glDrawArrays(drawType, drawStart, drawCount);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        // END TEMP



        // glEnableVertexAttribArray(0);
        // glEnableVertexAttribArray(1);
        // glEnableVertexAttribArray(2);

        // mActiveShader = nullptr;

        // for (auto it = mDrawComponents.begin(); it != mDrawComponents.end(); ++it) {
        //     if ((*it).expired()) {
        //         it = mDrawComponents.erase(it);
        //         it--;
        //         continue;
        //     }

        //     auto drawComp = (*it).lock();
        //     // std::cout << "I am drawing component " << drawComp->GetID() << std::endl;
        //     if (!drawComp)
        //         throw std::runtime_error("Draw Component couldn't be locked when trying to render it.");

        //     Program* curShader = drawComp->GetShader();
        //     if (mActiveShader != curShader) {
        //         mActiveShader = curShader;
        //     }

        //     if (!mActiveShader->IsInUse()) {
        //         // make the shader active 
        //         // std::cout << "Using a new shader!" << std::endl;
        //         mActiveShader->Use();

        //     // std::string materialName = drawComp->GetMaterialName();
        //     // mTextures->at(materialName)->BindTexture(mActiveShader);
        //     }

        //     if (!drawComp->Render(mActiveShader)) {
        //         throw std::runtime_error("The Draw Component wasn't drawn properly.");
        //     }

        //     // mTextures->at(materialName)->UnbindTexture();
        // }

        // glDisableVertexAttribArray(0);
        // glDisableVertexAttribArray(1);
        // glDisableVertexAttribArray(2);

        mShaders.at(0)->Stop();
        // mActiveShader->Stop();
        
        // swap the display buffers (displays what was just drawn)
        glfwSwapBuffers();
    }
}
