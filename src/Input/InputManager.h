#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <glm/glm.hpp>
#include <map>
#include <memory>

#include "Engine.h"
#include "Component.h"

typedef std::map<GLuint,std::shared_ptr<backlash::Component> > COMPONENT_LIST;

namespace backlash {
    class Engine;

    class InputManager {
        typedef std::shared_ptr<InputManager> InputSystem_ptr;
        typedef std::shared_ptr<Engine> Engine_ptr;

    public:
        static InputSystem_ptr GetInstance(Engine_ptr);
        
        ~InputManager() {}

        void AddCameraComponent(GLuint);
        void AddLightComponent(GLuint);

        void Init();

        void HandleInput(double);

    private:
        static InputSystem_ptr mInstance;

        const Engine_ptr mParent;

        GLuint mCameraComponentID;
        GLuint mLightComponentID; // temp


        // TODO: I can't do this yet. I don't know how to use threads. yet.
        // static void HandleKeyEvents(int key, int action);
        // static void HandleMousePosEvents(int xpos, int ypos);
        // static void HandleMouseWheelEvents(int pos);

        InputManager(Engine_ptr);

        // Don't Implement copy constructors
        InputManager(const InputManager&); 
        void operator=(const InputManager&);
    };

}

#endif