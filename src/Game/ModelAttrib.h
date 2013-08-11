#ifndef MODELATTRIB_H
#define MODELATTRIB_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp> // You may or may not need this

namespace backlash {
    struct ModelAttrib {
        glm::mat4 mTransform;

        glm::vec3 mPosition;
        glm::quat mOrientation;

        void UpdateTransform();
    };
}

#endif