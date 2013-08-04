#include "TranslateAlg.h"
#include "Algorithm.h"
#include "AIComponent.h"

namespace backlash  {
    TranslateAlg::TranslateAlg(AIComponent* comp) : 
        Algorithm(comp) {
            mDirection = glm::vec3(1.0f,0.0f,0.0f);
        }

    TranslateAlg::~TranslateAlg() {}

    void TranslateAlg::Action(double timeTick) {
        mTimer += timeTick;

        if (mTimer > 4) {
            mDirection *= -1;  
        }

        glm::vec3 offset(mDirection * timeTick);
        mPosition += offset;

        mCompParent->mAttrib->UpdateTransform();
    }  
}