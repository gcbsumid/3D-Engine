#ifndef ROTATEALG_H
#define ROTATEALG_H

// Standard Library
#include <memory>

// Backlash Library
#include "Algorithm.h"
#include "AIComponent.h"

namespace backlash {
    class RotateAlg : public Algorithm {
    public:
        RotateAlg(AIComponent* comp);

        ~RotateAlg();
        
        virtual void Action(double);

    private:
        glm::vec3 mDirection;
    };
}

#endif