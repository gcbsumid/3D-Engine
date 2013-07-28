#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "../Game/Engine.h"
#include "../Game/Component.h"

namespace backlash {
    class Engine;

    class InputManager {
        typedef std::shared_ptr<InputManager> InputSystemPtr;
        typedef std::weak_ptr<Engine> EnginePtr;

    public:
        static InputSystemPtr GetInstance(EnginePtr);
        ~InputManager() {}

        void AddCameraComponent(CameraComponent*);

        // Temporary
        void AddLightComponent(LightComponent*);

        // void Init(); // Don't need this right now.

        void HandleInput(double);

    private:
        static InputSystemPtr mInstance;

        const EnginePtr mParent;

        std::weak_ptr<CameraComponent> mCameraComponent;
        std::weak_ptr<LightComponent> mLightComponent; // temp


        // TODO: I can't do this yet. I don't know how to use threads. yet.
        // static void HandleKeyEvents(int key, int action);
        // static void HandleMousePosEvents(int xpos, int ypos);
        // static void HandleMouseWheelEvents(int pos);

        InputManager(EnginePtr);

        // Don't Implement copy constructors
        InputManager(const InputManager&); 
        void operator=(const InputManager&);
    };

}

#endif