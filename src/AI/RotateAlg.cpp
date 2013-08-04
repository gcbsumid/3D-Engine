#include "RotateAlg.h"
#include "Algorithm.h"
#include "AIComponent.h"

namespace backlash  {
    RotateAlg::RotateAlg(AIComponent* comp) : 
        Algorithm(comp) {
            mDirection = glm::vec3(1.0f,0.0f,0.0f);
        }

    RotateAlg::~RotateAlg() {}

    void RotateAlg::Action(double timeTick) {
        glm::quat offset(mDirection * timeTick);
        mCompParent->mAttrib->mOrientation *= offset;

        mCompParent->mAttrib->UpdateTransform();
    }  
}