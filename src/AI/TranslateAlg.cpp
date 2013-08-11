// Standard Library
#include <stdexcept>
#include <sstream>

// Backlash Library
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

        glm::vec3 offset(mDirection.x * timeTick,
                         mDirection.y * timeTick,
                         mDirection.z * timeTick);
        
        if (auto comp = mCompParent->mModel.lock()) {
            comp->mPosition += offset;
            comp->UpdateTransform();
        } else {
            std::stringstream msg; 
            msg << "mComponentParent (Component ID: " << mCompParent->GetID() << ") of an Algorithm could not be locked for translation." << std::endl;
            std::runtime_error(msg.str());
        }
    }  
}