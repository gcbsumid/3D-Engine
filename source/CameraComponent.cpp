#include "CameraComponent.h"

backlash::CameraComponent::CameraComponent(glm::vec2 screen_size) : backlash::EntityComponent(),
                                                                    mCamera(new backlash::Camera()) {
    mCamera->SetPosition(glm::vec3(0,0,4));
    mCamera->SetViewportAspectRatio(screen_size.x/screen_size.y);
    mCamera->SetNearAndFarPlanes(0.5f, 100.0f);
}

backlash::CameraComponent::~CameraComponent() {} 

void backlash::CameraComponent::Update() {
    // Probably do something?
}

std::shared_ptr<backlash::Camera> backlash::CameraComponent::GetCamera() const {
    return mCamera;
}