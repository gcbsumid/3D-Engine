#include "ModelAttrib.h"

namespace backlash {
    void ModelAttrib::UpdateTransform() {
        mTransform = glm::mat4();
        // glm::mat4 orientation = glm::mat4_cast(mOrientation);

        mTransform *= mOrientation;
        mTransform *= glm::translate(glm::mat4(), mPosition);
    }
}