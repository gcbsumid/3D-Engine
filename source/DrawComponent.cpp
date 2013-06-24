#include "DrawComponent.h"

backlash::DrawComponent::DrawComponent(GLuint id) : backlash::EntityComponent(), 
                                                    mAssetID(id),
                                                    mTransform(glm::mat4(1.0f)) {}

backlash::DrawComponent::~DrawComponent() {}

void backlash::DrawComponent::Update() {
    // Do something?
}

void backlash::DrawComponent::SetTransform(glm::mat4 transform) {
    // TODO: probably do some checks here to make sure transform is valid
    mTransform = transform;
}

glm::mat4 backlash::DrawComponent::GetTransform() {
    return mTransform;
}

GLuint backlash::DrawComponent::GetAssetID() const {
    return mAssetID;
}