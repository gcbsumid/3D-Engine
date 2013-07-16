#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "../Game/Component.h"
#include "Camera.h"
#include "../Util/enum.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>

// TODO: Move the individual render stuff for the camera here.

namespace backlash {
    class CameraComponent : public Component {
    friend class ComponentFactoryInitializer;
    friend class Factory;

    CameraComponent(glm::vec2);
    ~CameraComponent();

    class Factory: public ComponentFactory {
    friend class ComponentFactoryInitializer;
    public:
        Component* Create() {
            return new CameraComponent;
        }
    };

    public:
        virtual void Init();
        virtual void Update();
        virtual void Renderer();

        void InitCamera(glm::vec2);

        std::shared_ptr<Camera> GetCamera() const; 

    private:
        std::shared_ptr<Camera> mCamera;
    };
}

#endif