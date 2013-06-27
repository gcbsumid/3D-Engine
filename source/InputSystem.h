#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <glm/glm.hpp>
#include <map>
#include <memory>

#include "CameraComponent.h"
#include "EntityComponent.h"

typedef std::map<GLuint,std::shared_ptr<backlash::EntityComponent> > COMPONENT_LIST;

namespace backlash {
    class InputSystem {
    public:
        static std::shared_ptr<InputSystem> GetInstance();
        
        ~InputSystem() {}

        void AddCameraComponent(GLuint);
        void HandleInput(COMPONENT_LIST&, double);

    private:
        static std::shared_ptr<InputSystem> mInstance;

        GLuint mCameraComponentID;
        InputSystem();

        // Don't Implement copy constructors
        InputSystem(const InputSystem&); 
        void operator=(const InputSystem&);
    };

}

#endif