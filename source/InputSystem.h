#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <glm/glm.hpp>
#include <map>
#include <memory>

#include "Engine.h"
#include "EntityComponent.h"

typedef std::map<GLuint,std::shared_ptr<backlash::EntityComponent> > COMPONENT_LIST;

namespace backlash {
    class Engine;

    class InputSystem {
        typedef std::shared_ptr<InputSystem> InputSystem_ptr;
        typedef std::shared_ptr<Engine> Engine_ptr;

    public:
        static InputSystem_ptr GetInstance(Engine_ptr);
        
        ~InputSystem() {}

        void AddCameraComponent(GLuint);
        void AddLightComponent(GLuint);

        void Init();

        void HandleInput(double);

    private:
        static InputSystem_ptr mInstance;

        const Engine_ptr mParent;

        GLuint mCameraComponentID;
        GLuint mLightComponentID; // temp

        static void HandleKeyEvents(int key, int action);
        static void HandleMousePosEvents(int xpos, int ypos);
        static void HandleMouseWheelEvents(int pos);

        InputSystem(Engine_ptr);

        // Don't Implement copy constructors
        InputSystem(const InputSystem&); 
        void operator=(const InputSystem&);
    };

}

#endif