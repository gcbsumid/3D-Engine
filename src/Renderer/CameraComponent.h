#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"
#include "Camera.h"
#include "enum.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>

namespace backlash {
    class CameraComponent : public Component {
    public:
        CameraComponent(glm::vec2);
        ~CameraComponent();

        void Update();
        std::shared_ptr<Camera> GetCamera() const; 

    private:
        std::shared_ptr<Camera> mCamera;
    };
}

#endif