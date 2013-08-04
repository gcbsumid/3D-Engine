#ifndef ALGORITHM_H
#define ALGORITHM_H

// Standard Library
#include <memory>

// Backlash Library
#include "AIComponent.h"

namespace backlash {
    class Algorithm {
    public:
        Algorithm(AIComponent*);

        virtual ~Algorithm(); // Probably create this, just in case.

        virtual void Action(double) = 0; 

    protected:
        std::weak_ptr<AIComponent> mCompParent;
    };
}

#endif