#include "ModelAttrib.h"

namespace backlash {
    void ModelAttrib::UpdateTransform() {
        mTransform = glm::mat4();
        glm::mat4 orientation = glm::mat4_cast(mOrientation);

        mTransform *= orientation;
        mTransform = glm::translate(mTransform, -mPosition);
    }
}