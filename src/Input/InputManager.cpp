#include "InputManager.h"
#include "../Util/util.h"

#include <GL/glfw.h>

static const float mouseSensitivity = 0.1f;
static const float zoomSensitivity = 5.0f;

// Global static pointer used to ensure my singleton
backlash::InputManager* backlash::InputManager::mInstance{nullptr};

namespace backlash {
    InputManager::InputManager() {
        // TODO: you need to learn how to multi-thread

        // glfwSetMouseWheelCallback(InputManager::HandleMouseWheelEvents);
        // glfwSetMousePosCallback(InputManager::HandleMousePosEvents);
        // glfwSetKeyCallback(InputManager::HandleKeyEvents);
    }

    InputManager* InputManager::GetInstance() {
        if (!mInstance) {
            mInstance = new InputManager;
        }
        return mInstance;
    }

    void InputManager::AddCameraComponent(std::shared_ptr<CameraComponent> comp) {
        assert(comp.use_count());

        mCameraComponent = comp;
    }

    void InputManager::AddLightComponent(std::shared_ptr<LightComponent> comp) {
        assert(comp.use_count());

        mLightComponent = comp;
    }

    void InputManager::HandleInput(double elapsedTime) {
        assert(mCameraComponent.use_count());
        assert(mLightComponent.use_count());

        // move position based on wasd keys
        if (glfwGetKey('S')) {
            mCameraComponent->MoveCamera(elapsedTime, -mCameraComponent->Forward());
        } else if (glfwGetKey('W')) {
            mCameraComponent->MoveCamera(elapsedTime, mCameraComponent->Forward());
        }

        if (glfwGetKey('A')){
            mCameraComponent->MoveCamera(elapsedTime, -mCameraComponent->Right());
        } else if (glfwGetKey('D')){
            mCameraComponent->MoveCamera(elapsedTime, mCameraComponent->Right());
        }

        if (glfwGetKey('X')){
            mCameraComponent->MoveCamera(elapsedTime, -mCameraComponent->Up());
        } else if (glfwGetKey('Z')){
            mCameraComponent->MoveCamera(elapsedTime, mCameraComponent->Up());
        }

        if (glfwGetKey('1')) {
            mLightComponent->SetPosition(mCameraComponent->Position());
        }

        if (glfwGetKey('2')) {
            // Set Colour to red
            mLightComponent->SetIntensity(glm::vec3(1,0,0)); 
        } else if (glfwGetKey('3')) {
            // Set Colour to green
            mLightComponent->SetIntensity(glm::vec3(0,1,1));         
        } else if (glfwGetKey('4')) {
            // Set Colour to white
            mLightComponent->SetIntensity(glm::vec3(1,1,1));         
        }


        // View rotation based on mouse movements
        int mouseX = 0, mouseY = 0;
        glfwGetMousePos(&mouseX, &mouseY);
        mCameraComponent->OffsetOrientation(mouseSensitivity * mouseY, mouseSensitivity * mouseX);
        glfwSetMousePos(0,0);

        float fieldOfView = mCameraComponent->FieldOfView() + zoomSensitivity * (float)glfwGetMouseWheel();
        if (fieldOfView < 5.0f) {
            fieldOfView = 5.0f;
        }
        if (fieldOfView > 130.0f) {
            fieldOfView = 130.0f;
        }
        mCameraComponent->SetFieldOfView(fieldOfView);
        glfwSetMouseWheel(0);

    }

    // void GLFWCALL InputManager::HandleKeyEvents(int key, int action) {
    //     // TODO: Everything in here.
    // }

    // void GLFWCALL InputManager::HandleMousePosEvents(int xpos, int ypos) {
    //     // TODO: Everything in here.
    // }

    // void GLFWCALL InputManager::HandleMouseWheelEvents(int pos) {
    //     // TODO: Everything in here.
    // }
}
