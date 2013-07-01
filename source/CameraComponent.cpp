#include "CameraComponent.h"

namespace backlash {
    CameraComponent::CameraComponent(glm::vec2 screen_size) : 
            EntityComponent(E_COMPONENT::E_COMPONENT_CAMERA),
            mCamera(new Camera()) {
        mCamera->SetPosition(glm::vec3(0,0,4));
        mCamera->SetViewportAspectRatio(screen_size.x/screen_size.y);
        mCamera->SetNearAndFarPlanes(0.5f, 100.0f);
    }

    CameraComponent::~CameraComponent() {} 

    void CameraComponent::Update() {
        // Probably do something?
    }

    std::shared_ptr<Camera> CameraComponent::GetCamera() const {
        return mCamera;
    }    
}