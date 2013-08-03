#include "RotateAlg.h"
#include "AIComponent.h"

namespace backlash  {
    RotateAlg::RotateAlg(Algorithm::AICompPtr comp) : 
        Algorithm(comp) {}

    RotateAlg::RotateAlg(Algorithm::AICompPtr comp, 
                         shared_ptr<Algorithm> child) : 
        Algorithm(comp, child) {
            // For now, just set a default rotation direction
            mDirection = glm::vec3(1.0f,0.0f,0.0f);
        }

    RotateAlg::~RotateAlg() {}

    void RotateAlg::Action(double timeTick) {
        glm::quat offset(mDirection * timeTick);
        mAttrib->mOrientation *= offset;

        mAttrib->UpdateTransform();
    }  
}