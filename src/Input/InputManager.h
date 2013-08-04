#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

// GLM Library
#include <glm/glm.hpp>

// Standard Library 
#include <memory>

// Backlash Library
#include "../Game/Engine.h"
#include "../Renderer/CameraComponent.h"
#include "../Renderer/mLightComponent.h"

namespace backlash {
    class InputManager {
    public:
        static InputManager* GetInstance(Engine*);
        ~InputManager() {}

        void AddCameraComponent(CameraComponent*);

        // Temporary
        void AddLightComponent(LightComponent*);

        // void Init(); // Don't need this right now.

        void HandleInput(double);

    private:
        static InputManager* mInstance;

        const std::weak_ptr<Engine> mParent;

        std::weak_ptr<CameraComponent> mCameraComponent;
        std::weak_ptr<LightComponent> mLightComponent; // eventually, this will become a vector of lights

        // static void HandleKeyEvents(int key, int action);
        // static void HandleMousePosEvents(int xpos, int ypos);
        // static void HandleMouseWheelEvents(int pos);

        InputManager(Engine*);

        // Don't Implement copy constructors
        InputManager(const InputManager&); 
        void operator=(const InputManager&);
    };

}

#endif