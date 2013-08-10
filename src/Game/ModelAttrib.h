#ifndef MODELATTRIB_H
#define MODELATTRIB_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp> // You may or may not need this

namespace backlash {
    struct ModelAttrib {
        glm::mat4 mTransform;

        glm::vec3 mPosition;
        glm::quat mOrientation;

        void UpdateTransform();
    };

    void ModelAttrib::UpdateTransform() {
        mTransform = glm::mat4();
        glm::mat4 orientation = glm::mat4_cast(mOrientation);

        mTransform *= orientation;
        mTransform = glm::translate(mTransform, -mPosition);
    }
}

#endif