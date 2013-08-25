#ifndef MODELATTRIB_H
#define MODELATTRIB_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/quaternion.hpp> // You may or may not need this
#include "../Renderer/AABB.h"

namespace backlash {
    struct ModelAttrib {
        glm::mat4 mTransform;

        glm::vec3 mPosition;
        // glm::quat mOrientation;

        glm::mat4 mOrientation;
        glm::vec3 mScale;
        AABB mBoundingBox; 

        void UpdateTransform();
        AABB ComputeBoundingBox();
        
        void DisplayModelAttrib();
    };
}

#endif