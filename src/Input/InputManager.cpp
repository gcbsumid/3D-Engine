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

    void InputManager::AddCameraComponent(GLuint id) {
        assert(utility::IsValidComponentID(id));

        mCameraComponentID = id;
    }

    void InputManager::AddLightComponent(GLuint id) {
        assert(utility::IsValidComponentID(id));

        mLightComponentID = id;
    }

    // void InputManager::Init() {
        // TODO: you need to learn how to multi-thread

        // glfwSetMouseWheelCallback(InputManager::HandleMouseWheelEvents);
        // glfwSetMousePosCallback(InputManager::HandleMousePosEvents);
        // glfwSetKeyCallback(InputManager::HandleKeyEvents);
    // }

    void InputManager::HandleInput(double elapsedTime) {
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
