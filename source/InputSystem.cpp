#include "InputSystem.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "Camera.h"
#include "util.h"

#include <GL/glfw.h>

static const float mouseSensitivity = 0.1f;
static const float zoomSensitivity = 5.0f;

// Global static pointer used to ensure my singleton
std::shared_ptr<backlash::InputSystem> backlash::InputSystem::mInstance;

backlash::InputSystem::InputSystem() : mCameraComponentID(UINT_MAX), mLightComponentID(UINT_MAX) {}

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

void backlash::InputSystem::AddLightComponent(GLuint id) {
    assert(utility::IsValidComponentID(id));

    mLightComponentID = id;
}

void backlash::InputSystem::HandleInput(COMPONENT_LIST& components, double elapsedTime) {
    // TODO: Change Event handling from polling to using callbacks. 
    //       Link: http://content.gpwiki.org/index.php/GLFW:Tutorials:Basics#Input

    assert(utility::IsValidComponentID(mCameraComponentID));

    auto cameraComponent = std::static_pointer_cast<backlash::CameraComponent>(components.at(mCameraComponentID));
    auto camera = cameraComponent->GetCamera();
    auto light = std::static_pointer_cast<backlash::LightComponent>(components.at(mLightComponentID));

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

    if (glfwGetKey('1')) {
        light->SetPosition(camera->Position());
    }

    if (glfwGetKey('2')) {
        // Set Colour to red
        light->SetIntensity(glm::vec3(1,0,0)); 
    } else if (glfwGetKey('3')) {
        // Set Colour to green
        light->SetIntensity(glm::vec3(0,1,1));         
    } else if (glfwGetKey('4')) {
        // Set Colour to white
        light->SetIntensity(glm::vec3(1,1,1));         
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