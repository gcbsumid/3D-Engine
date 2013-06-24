#include "GraphicsSystem.h"
#include "Program.h"
#include "util.h"
#include "ModelAsset.h"
#include <cassert>

void backlash::GraphicsSystem::AddDrawComponent(GLuint id) {
    assert(utility::IsValidComponentID(id));

    mDrawComponentIDs.push_back(id);
}

void backlash::GraphicsSystem::AddCameraComponent(GLuint id) {
    assert(utility::IsValidComponentID(id));

    mCameraID = id;
}

void backlash::GraphicsSystem::Render(const std::map<GLuint,backlash::DrawComponent>& components
                                      const std::map<GLuint,backlash::ModelAsset>& assets) const {
    /* TODO: Lets have it like this for now. Maybe you can figure out later where the 
     *       Assets should actually be located ~ either as a global variable or as a 
     *       member of the Graphics System.
     */

    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render all instances
    backlash::Program* current = NULL;
    for (auto compID : mDrawComponentIDs) {
        auto asset = assets.at(compID);

        if (!asset->mShaders->IsInUse()) {
            if (current && current->IsInUse()) {
                current->Stop();
            }
            current = asset->mShaders;
            current->Use();
        }
        RenderInstance(components.at(compID), asset, components.at(mCameraID));
    }
    current->Stop();

    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers();
}

void backlash::GraphicsSystem::RenderInstance(const backlash::DrawComponent& comp, 
                                              const backlash::ModelAsset& asset,
                                              const backlash::CameraComponent& camera) const {
    backlash::Program* shaders = asset.mShaders;

    // set shader uniforms
    shaders->SetUniform("camera", camera->Matrix());
    shaders->SetUniform("model", comp.mTransform);
    shaders->SetUniform("tex", 0); // texture is bounded to GL_TEXTURE0

    // bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, asset.mTextures->Object());

    /* Note: Consider using glDrawArraysInstanced instead
     *       of glDrawArrays. You can get better performance.
     */
    // bind VAO and draw 
    glBindVertexArray(asset.mVAO);
    glDrawArrays(asset.mDrawType, asset.mDrawStart, asset.mDrawCount);

    // unbind everything
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

}