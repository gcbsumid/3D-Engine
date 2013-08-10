#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

// GLM Library
#include <glm/glm.hpp>

// Standard Library 
#include <memory>

// Backlash Library
#include "../Renderer/CameraComponent.h"
#include "../Renderer/LightComponent.h"

namespace backlash {
    class InputManager {
    public:
        static InputManager* GetInstance();
        ~InputManager() {}

        void AddCameraComponent(std::shared_ptr<CameraComponent>);

        // Temporary
        void AddLightComponent(std::shared_ptr<LightComponent>);

        void HandleInput(double);

    private:
        static InputManager* mInstance;

        std::weak_ptr<CameraComponent> mCameraComponent;
        std::weak_ptr<LightComponent> mLightComponent; // eventually, this will become a vector of lights

        // static void HandleKeyEvents(int key, int action);
        // static void HandleMousePosEvents(int xpos, int ypos);
        // static void HandleMouseWheelEvents(int pos);

        InputManager();

        // Don't Implement copy constructors
        InputManager(const InputManager&); 
        void operator=(const InputManager&);
    };

}

#endif