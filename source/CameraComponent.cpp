#include "CameraComponent.h"

backlash::CameraComponent::CameraComponent(glm::vec2 screen_size) : backlash::EntityComponent() {
    mCamera.SetPosition(glm::vec3(0,0,4));
    mCamera.SetViewportAspectRatio(screen_size.x, screen_size.y);
}

backlash::CameraComponent::~CameraComponent() {} 

void backlash::CameraComponent::Update() {
    // Probably do something?
}

unique_ptr<Camera> backlash::CameraComponent::GetCamera() {
    return mCamera;
}