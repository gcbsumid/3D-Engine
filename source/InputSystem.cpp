#include "InputSystem.h"
#include "Camera.h"
#include "util.h"

#include <GL/glfw.h>

static const float mouseSensitivity = 0.1f;
static const float zoomSensitivity = 5.0f;

// Global static pointer used to ensure my singleton
std::shared_ptr<backlash::InputSystem> backlash::InputSystem::mInstance;

backlash::InputSystem::InputSystem() : mCameraComponentID(-1) {}

std::shared_ptr<backlash::InputSystem> backlash::InputSystem::GetInstance() {
    if (mInstance.use_count() < 1) {
        mInstance = std::shared_ptr<backlash::InputSystem>(new backlash::InputSystem);
    }
    return mInstance;
}


void backlash::InputSystem::AddCameraComponent(GLuint id) {
    assert(utility::IsValidComponentID(id));

    mCameraComponentID = id;
}

void backlash::InputSystem::HandleInput(COMPONENT_LIST& components, double elapsedTime) {
    assert(utility::IsValidComponentID(mCameraComponentID));

    auto cameraComponent = std::static_pointer_cast<backlash::CameraComponent>(components.at(mCameraComponentID));
    auto camera = cameraComponent->GetCamera();

    // move position based on wasd keys
    if (glfwGetKey('S')) {
        camera->MoveCamera(elapsedTime, -camera->Forward());
    } else if (glfwGetKey('W')) {
        camera->MoveCamera(elapsedTime, camera->Forward());
    }

    if (glfwGetKey('A')){
        camera->MoveCamera(elapsedTime, -camera->Right());
    } else if (glfwGetKey('D')){
        camera->MoveCamera(elapsedTime, camera->Right());
    }

    if (glfwGetKey('X')){
        camera->MoveCamera(elapsedTime, -camera->Up());
    } else if (glfwGetKey('Z')){
        camera->MoveCamera(elapsedTime, camera->Up());
    }

    // View rotation based on mouse movements
    int mouseX = 0, mouseY = 0;
    glfwGetMousePos(&mouseX, &mouseY);
    camera->OffsetOrientation(mouseSensitivity * mouseY, mouseSensitivity * mouseX);
    glfwSetMousePos(0,0);

    float fieldOfView = camera->FieldOfView() + zoomSensitivity * (float)glfwGetMouseWheel();
    if (fieldOfView < 5.0f) {
        fieldOfView = 5.0f;
    }
    if (fieldOfView > 130.0f) {
        fieldOfView = 130.0f;
    }
    camera->SetFieldOfView(fieldOfView);
    glfwSetMouseWheel(0);

}