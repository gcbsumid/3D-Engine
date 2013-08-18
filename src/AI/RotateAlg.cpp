// GLM Library
#include <glm/glm.hpp>

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
        // glm::quat offset(1.0, 
        //                  mDirection.x * timeTick, 
        //                  mDirection.y * timeTick,
        //                  mDirection.z * timeTick);
        if (auto model = mCompParent->mModel.lock()) {
            // model->mOrientation = model->mOrientation * offset;
            glm::mat4 orientation;
            model->mOrientation = glm::rotate(orientation, 360.0f * (float)timeTick, mDirection);

            model->UpdateTransform();
        } else {
            std::stringstream msg; 
            msg << "mComponentParent (Component ID: " << mCompParent->GetID() << ") of an Algorithm could not be locked for rotation" << std::endl;
            std::runtime_error(msg.str());
        }
    }  
}