#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "EntityComponent.h"
#include "Camera.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>

namespace backlash {
    class CameraComponent : public EntityComponent {
    public:
        CameraComponent(glm::vec2);
        ~CameraComponent();

        void Update();
        unique_ptr<Camera> GetCamera();

    private:
        unique_ptr<Camera> mCamera;
    };
}

#endif