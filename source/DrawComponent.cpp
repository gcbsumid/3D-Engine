#include "DrawComponent.h"

namespace backlash {
    DrawComponent::DrawComponent(GLuint id) : 
        EntityComponent(E_COMPONENT::E_COMPONENT_DRAW), 
        mAssetID(id),
        mTransform(glm::mat4(1.0f)){}

    DrawComponent::~DrawComponent() {}

    void DrawComponent::Update() {
        // Do something?
    }

    void DrawComponent::SetTransform(glm::mat4 transform) {
        mTransform = transform;
    }

    glm::mat4 DrawComponent::GetTransform() const {
        return mTransform;
    }

    GLuint DrawComponent::GetAssetID() const {
        return mAssetID;
    }    
}