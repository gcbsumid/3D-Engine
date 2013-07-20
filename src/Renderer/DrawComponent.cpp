#include "DrawComponent.h"

namespace backlash {
    DrawComponent::DrawComponent() : 
        Component(E_COMPONENT::E_COMPONENT_DRAW) {}

    DrawComponent::~DrawComponent() {}

    void DrawComponent::Init() {
        // Do something?
    }

    void DrawComponent::Update() {
        // Do something?
    }

    bool DrawComponent::Render() {
        // Do the rendering here

        return true;
    }

    void DrawComponent::SetAsset(int id) {
        mAssetID = id;
    }

    void DrawComponent::SetModelAttrib(std::shareD_ptr<ModelAttrib> model) {
        mModel = model;
    }

    glm::mat4 DrawComponent::GetTransform() const {
        return mTransform;
    }

    int DrawComponent::GetAssetID() const {
        return mAssetID;
    }    
}