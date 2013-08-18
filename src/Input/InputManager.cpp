#include <GL/glew.h>
#include <GL/glfw.h>

#include <iostream>

#include "InputManager.h"
#include "../Util/util.h"
#include "../Util/defines.h"


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

        auto cameraComp = mCameraComponent.lock();
        auto lightComp = mLightComponent.lock();

        if (!cameraComp) {
            std::runtime_error("Invalid camera component.");
        }

        if (!lightComp) {
            std::runtime_error("Invalid light component.");
        }
        // move position based on wasd keys
        if (glfwGetKey('S')) {
            // std::cout << "Moving backwards!" << std::endl;
            cameraComp->MoveCamera(elapsedTime, -cameraComp->Forward());
        } else if (glfwGetKey('W')) {
            // std::cout << "Moving forward!" << std::endl;
            cameraComp->MoveCamera(elapsedTime, cameraComp->Forward());
        }

        if (glfwGetKey('A')){
            // std::cout << "Strafing left!" << std::endl;
            cameraComp->MoveCamera(elapsedTime, -cameraComp->Right());
        } else if (glfwGetKey('D')){
            // std::cout << "Strafing right!" << std::endl;
            cameraComp->MoveCamera(elapsedTime, cameraComp->Right());
        }

        if (glfwGetKey('X')){
            // std::cout << "Moving down!" << std::endl;
            cameraComp->MoveCamera(elapsedTime, -cameraComp->Up());
        } else if (glfwGetKey('Z')){
            // std::cout << "Moving up!" << std::endl;
            cameraComp->MoveCamera(elapsedTime, cameraComp->Up());
        }

        if (glfwGetKey('1')) {
            // std::cout << "Setting the camera position to: ";
            glm::vec3 pos = cameraComp->Position();
            lightComp->SetPosition(pos);
            // std::cout << "(" << pos.x << "," << pos.y << "," << pos.z << ")" << std::endl;
        }

        if (glfwGetKey('2')) {
            // Set Colour to red
            // std::cout << "Setting the light color to: red" << std::endl;
            lightComp->SetIntensity(glm::vec3(1,0,0)); 
        } else if (glfwGetKey('3')) {
            // Set Colour to green
            // std::cout << "Setting the light color to: green" << std::endl;
            lightComp->SetIntensity(glm::vec3(0,1,1));         
        } else if (glfwGetKey('4')) {
            // Set Colour to white
            // std::cout << "Setting the light color to white" << std::endl;
            lightComp->SetIntensity(glm::vec3(1,1,1));         
        }


        // View rotation based on mouse movements
        int mouseX = 0, mouseY = 0;
        glfwGetMousePos(&mouseX, &mouseY);
        if (mouseX || mouseY) {
            cameraComp->OffsetOrientation(utility::MOUSE_SENSITIVITY * mouseY, utility::MOUSE_SENSITIVITY * mouseX);
            glfwSetMousePos(0,0);
        }

        if (glfwGetMouseWheel()) {
            float fieldOfView = cameraComp->FieldOfView() + utility::ZOOM_SENSITIVITY * (float)glfwGetMouseWheel();
            if (fieldOfView < 5.0f) {
                fieldOfView = 5.0f;
            }
            if (fieldOfView > 130.0f) {
                fieldOfView = 130.0f;
            }
            cameraComp->SetFieldOfView(fieldOfView);
            glfwSetMouseWheel(0);
        }

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
