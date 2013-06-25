#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <glm/glm.hpp>
#include <map>

#include "CameraComponent.h"
#include "EntityComponent.h"

typedef std::map<GLuint,std::shared_ptr<backlash::EntityComponent> > COMPONENT_LIST;

namespace backlash {
    class InputSystem {
    public:
        static InputSystem& getInstance() {
            static InputSystem instance;
            return instance;
        }

        ~InputSystem() {}

        void AddCameraComponent(GLuint);
        void HandleInput(COMPONENT_LIST&, double);

    private:
        GLuint mCameraComponentID;
        InputSystem();

        // Don't Implement copy constructors
        InputSystem(const InputSystem&); 
        void operator=(const InputSystem&);
    };

}

#endif