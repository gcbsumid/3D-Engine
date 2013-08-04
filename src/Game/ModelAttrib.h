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

    void UpdateTransform() {
        mAttrib->mTransform = glm::mat4();
        glm::mat4 orientation = glm::quaternion::toMat4(mAttrib->mOrientation);

        mAttrib->mTransform *= orientation;
        mAttrib->mTransform = glm::translate(mAttrib->mTransform, -Position());
    }
}

#endif