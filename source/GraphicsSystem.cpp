#include "GraphicsSystem.h"
#include "Program.h"
#include "util.h"
#include "ModelAsset.h"
#include <cassert>
#include <iostream>

// Global static pointer used to ensure my singleton
std::shared_ptr<backlash::GraphicsSystem> backlash::GraphicsSystem::mInstance;

std::shared_ptr<backlash::GraphicsSystem> backlash::GraphicsSystem::GetInstance() {
    if (mInstance.get() == 0) {
        mInstance = std::shared_ptr<backlash::GraphicsSystem>(new backlash::GraphicsSystem);
    }
    return mInstance;
}

backlash::GraphicsSystem::GraphicsSystem() : mCameraComponentID(UINT_MAX) {}

void backlash::GraphicsSystem::AddDrawComponent(GLuint id) {
    assert(utility::IsValidComponentID(id));

    mDrawComponentIDs.push_back(id);
}

void backlash::GraphicsSystem::AddCameraComponent(GLuint id) {
    assert(utility::IsValidComponentID(id));

    mCameraComponentID = id;
}

void backlash::GraphicsSystem::Render(COMPONENT_LIST& components, 
                                      ASSET_LIST& assets) const {
    /* TODO: Lets have it like this for now. Maybe you can figure out later where the 
     *       Assets should actually be located ~ either as a global variable or as a 
     *       member of the Graphics System.
     */
    typedef std::shared_ptr<backlash::DrawComponent> DRAWCOMP_PTR;
    typedef std::shared_ptr<backlash::CameraComponent> CAMERACOMP_PTR;

    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render all instances
    assert(utility::IsValidComponentID(mCameraComponentID));
    std::shared_ptr<backlash::Program> current = NULL;
    for (auto compID : mDrawComponentIDs) {
        DRAWCOMP_PTR drawComponent = std::static_pointer_cast<backlash::DrawComponent>(components.at(compID));
        auto asset = assets.at(drawComponent->GetAssetID());
        if (!asset->mShaders->IsInUse()) {
            if (current && current->IsInUse()) {
                current->Stop();
            }
            current = asset->mShaders;
            current->Use();
        }
        RenderInstance(drawComponent, 
                       asset, 
                       std::static_pointer_cast<backlash::CameraComponent>(components.at(mCameraComponentID)));
    }
    current->Stop();

    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers();
}

void backlash::GraphicsSystem::RenderInstance(std::shared_ptr<backlash::DrawComponent> renderComp, 
                                              std::shared_ptr<backlash::ModelAsset> asset,
                                              std::shared_ptr<backlash::CameraComponent> cameraComp) const {
    auto shaders = asset->mShaders;
    auto camera = cameraComp->GetCamera();

    // set shader uniforms
    shaders->SetUniform("camera", camera->Matrix());
    shaders->SetUniform("model", renderComp->GetTransform());
    shaders->SetUniform("tex", 0); // texture is bounded to GL_TEXTURE0

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