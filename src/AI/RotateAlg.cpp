// Standard Library 
#include <stdexcept>
#include <sstream>

// Backlash Library
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
        glm::quat offset(1.0, 
                         mDirection.x * timeTick, 
                         mDirection.y * timeTick,
                         mDirection.z * timeTick);
        if (auto comp = mCompParent->mModel.lock()) {
            comp->mOrientation = comp->mOrientation * offset;

            comp->UpdateTransform();
        } else {
            std::stringstream msg; 
            msg << "mComponentParent (Component ID: " << mCompParent->GetID() << ") of an Algorithm could not be locked for rotation" << std::endl;
            std::runtime_error(msg.str());
        }
    }  
}