#ifndef TRANSLATEALG_H
#define TRANSLATEALG_H

// GLM Library
#include <glm/glm.hpp>

// Standard Library
#include <memory>

// Backlash Library
#include "Algorithm.h"
#include "AIComponent.h"

namespace backlash {
    class TranslateAlg : public Algorithm {
    public:
        TranslateAlg(AIComponent* comp);

        ~TranslateAlg();
        
        virtual void Action(double);

    private:
        double mTimer;
        glm::vec3 mDirection;
    };
}

#endif