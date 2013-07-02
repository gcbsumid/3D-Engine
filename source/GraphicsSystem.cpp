#include "GraphicsSystem.h"
#include "Program.h"
#include "util.h"
#include <cassert>
#include <iostream>

// Global static pointer used to ensure my singleton
std::shared_ptr<backlash::GraphicsSystem> backlash::GraphicsSystem::mInstance;

// Typedefs 

typedef std::shared_ptr<backlash::DrawComponent> DRAWCOMP_PTR;
typedef std::shared_ptr<backlash::CameraComponent> CAMERACOMP_PTR;
typedef std::shared_ptr<backlash::LightComponent> LIGHTCOMP_PTR;
typedef std::shared_ptr<backlash::ModelAsset> MODELASSET_PTR;


namespace backlash {
    GraphicsSystem::GraphicsSystem_ptr GraphicsSystem::GetInstance(
        GraphicsSystem::Engine_ptr parent) {
        if (mInstance.get() == 0) {
            mInstance = std::shared_ptr<GraphicsSystem>(new GraphicsSystem(parent));
        }
        return mInstance;
    }

    GraphicsSystem::GraphicsSystem(GraphicsSystem::Engine_ptr parent) : 
            mParent(parent), 
            mCameraComponentID(UINT_MAX) {}

    void GraphicsSystem::AddDrawComponent(GLuint id) {
        assert(utility::IsValidComponentID(id));

        mDrawComponentIDs.push_back(id);
    }

    void GraphicsSystem::AddCameraComponent(GLuint id) {
        assert(utility::IsValidComponentID(id));

        mCameraComponentID = id;
    }

    void GraphicsSystem::AddLightComponent(GLuint id) {
        assert(utility::IsValidComponentID(id));

        mLightComponentIDs.push_back(id);
    }

    void GraphicsSystem::Render() const {
        /* TODO: Lets have it like this for now. Maybe you can figure out later where the 
         *       Assets should actually be located ~ either as a global variable or as a 
         *       member of the Graphics System.
         */

        // clear everything
        glClearColor(0, 0, 0, 1); // black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render all instances
        auto lightID = mLightComponentIDs.at(0);
        assert(utility::IsValidComponentID(mCameraComponentID));
        assert(utility::IsValidComponentID(lightID));

        auto lightComp = std::static_pointer_cast<LightComponent>(mParent->GetComponent(lightID));
        std::shared_ptr<Program> current = NULL;
        for (auto compID : mDrawComponentIDs) {
            auto drawComponent = std::static_pointer_cast<DrawComponent>(mParent->GetComponent(compID));
            auto asset = mParent->GetAsset(drawComponent->GetAssetID());
            if (!asset->mShaders->IsInUse()) {
                if (current && current->IsInUse()) {
                    current->Stop();
                }
                current = asset->mShaders;
                current->Use();
            }
            auto cameraComp = std::static_pointer_cast<CameraComponent>(mParent->GetComponent(mCameraComponentID));
            RenderInstance(drawComponent, 
                           asset, 
                           lightComp,
                           cameraComp);
        }
        current->Stop();

        // swap the display buffers (displays what was just drawn)
        glfwSwapBuffers();
    }

    void GraphicsSystem::RenderInstance(DRAWCOMP_PTR renderComp, 
                                        MODELASSET_PTR asset,
                                        LIGHTCOMP_PTR lightComp,
                                        CAMERACOMP_PTR cameraComp) const {
        auto shaders = asset->mShaders;
        auto camera = cameraComp->GetCamera();

        // set shader uniforms
        shaders->SetUniform("camera", camera->Matrix());
        shaders->SetUniform("model", renderComp->GetTransform());
        shaders->SetUniform("material.tex", 0); // texture is bounded to GL_TEXTURE0
        shaders->SetUniform("material.shininess", asset->mShininess);
        shaders->SetUniform("material.specularColor", asset->mSpecularColor);
        shaders->SetUniform("light.position", lightComp->GetPosition());
        shaders->SetUniform("light.intensities", lightComp->GetIntensity());
        shaders->SetUniform("light.attenuation", lightComp->GetAttenuation());
        shaders->SetUniform("light.ambientCoefficient", lightComp->GetAmbientCoefficient());
        shaders->SetUniform("cameraPosition", camera->Position());

        // bind the texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, asset->mTextures->Object());

        /* Note: Consider using glDrawArraysInstanced instead
         *       of glDrawArrays. You can get better performance.
         */
        // bind VAO and draw 
        glBindVertexArray(asset->mVAO);
        glDrawArrays(asset->mDrawType, asset->mDrawStart, asset->mDrawCount);

        // unbind everything
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);

    }    
}
