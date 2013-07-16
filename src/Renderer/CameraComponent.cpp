#include "CameraComponent.h"

namespace backlash {
    CameraComponent::CameraComponent() : 
        Component(E_COMPONENT::E_COMPONENT_CAMERA) {}
        
    CameraComponent::~CameraComponent() {} 

    void CameraComponent::Init() {
        // Do something?
    }

    void CameraComponent::Update() {
        // Probably do something?
    }

    void CameraComponent::Render() {
        // Not terribly sure what I should do here yet. 
    }

    void CameraComponent::InitCamera(glm::vec2 screen_size) {
        mCamera = std::shared_ptr<Camera>(new Camera);
        mCamera->SetPosition(glm::vec3(0,0,4));
        mCamera->SetViewportAspectRatio(screen_size.x/screen_size.y);
        mCamera->SetNearAndFarPlanes(0.5f, 100.0f);
    }

    std::shared_ptr<Camera> CameraComponent::GetCamera() const {
        return mCamera;
    }    
}