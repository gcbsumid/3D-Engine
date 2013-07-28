#include "InputManager.h"
#include "../Renderer/CameraComponent.h"
#include "../Renderer/LightComponent.h"
#include "../Renderer/Camera.h"
#include "../Util/util.h"

#include <GL/glfw.h>

static const float mouseSensitivity = 0.1f;
static const float zoomSensitivity = 5.0f;

// Global static pointer used to ensure my singleton
std::shared_ptr<backlash::InputManager> backlash::InputManager::mInstance;

namespace backlash {
    InputManager::InputManager(EnginePtr parent) : 
            mParent(parent),
            mCameraComponentID(UINT_MAX), 
            mLightComponentID(UINT_MAX) {}

    std::shared_ptr<InputManager> InputManager::GetInstance(EnginePtr parent) {
        if (mInstance.use_count() < 1) {
            mInstance = std::shared_ptr<InputManager>(new InputManager(parent));
        }
        return mInstance;
    }

    void InputManager::AddCameraComponent(CameraComponent* comp) {
        assert(comp);

        mCameraComponent = std::weak_ptr<CameraComponent> (comp);
    }

    void InputManager::AddLightComponent(LightComponent* comp) {
        assert(comp);

        mLightComponent = std::weak_ptr<LightComponent> (comp);
    }

    // void InputManager::Init() {
        // TODO: you need to learn how to multi-thread

        // glfwSetMouseWheelCallback(InputManager::HandleMouseWheelEvents);
        // glfwSetMousePosCallback(InputManager::HandleMousePosEvents);
        // glfwSetKeyCallback(InputManager::HandleKeyEvents);
    // }

    void InputManager::HandleInput(double elapsedTime) {
        assert(mCameraComponent.use_count());

        // auto cameraComp = std::static_pointer_cast<CameraComponent>(mParent->GetComponent(mCameraComponentID));
        // auto camera = cameraComp->GetCamera();
        // auto lightComp = std::static_pointer_cast<LightComponent>(mParent->GetComponent(mLightComponentID));

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
