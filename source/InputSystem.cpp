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

namespace backlash {
    InputSystem::InputSystem(Engine_ptr parent) : 
            mParent(parent),
            mCameraComponentID(UINT_MAX), 
            mLightComponentID(UINT_MAX) {}

    std::shared_ptr<InputSystem> InputSystem::GetInstance(Engine_ptr parent) {
        if (mInstance.use_count() < 1) {
            mInstance = std::shared_ptr<InputSystem>(new InputSystem(parent));
        }
        return mInstance;
    }

    void InputSystem::AddCameraComponent(GLuint id) {
        assert(utility::IsValidComponentID(id));

        mCameraComponentID = id;
    }

    void InputSystem::AddLightComponent(GLuint id) {
        assert(utility::IsValidComponentID(id));

        mLightComponentID = id;
    }

    void InputSystem::Init() {
        // TODO: you need to learn how to multi-thread

        // glfwSetMouseWheelCallback(InputSystem::HandleMouseWheelEvents);
        // glfwSetMousePosCallback(InputSystem::HandleMousePosEvents);
        // glfwSetKeyCallback(InputSystem::HandleKeyEvents);
    }

    void InputSystem::HandleInput(double elapsedTime) {
        assert(utility::IsValidComponentID(mCameraComponentID));

        auto cameraComp = std::static_pointer_cast<CameraComponent>(mParent->GetComponent(mCameraComponentID));
        auto camera = cameraComp->GetCamera();
        auto lightComp = std::static_pointer_cast<LightComponent>(mParent->GetComponent(mLightComponentID));

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
            lightComp->SetPosition(camera->Position());
        }

        if (glfwGetKey('2')) {
            // Set Colour to red
            lightComp->SetIntensity(glm::vec3(1,0,0)); 
        } else if (glfwGetKey('3')) {
            // Set Colour to green
            lightComp->SetIntensity(glm::vec3(0,1,1));         
        } else if (glfwGetKey('4')) {
            // Set Colour to white
            lightComp->SetIntensity(glm::vec3(1,1,1));         
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

    // void GLFWCALL InputSystem::HandleKeyEvents(int key, int action) {
    //     // TODO: Everything in here.
    // }

    // void GLFWCALL InputSystem::HandleMousePosEvents(int xpos, int ypos) {
    //     // TODO: Everything in here.
    // }

    // void GLFWCALL InputSystem::HandleMouseWheelEvents(int pos) {
    //     // TODO: Everything in here.
    // }
}
