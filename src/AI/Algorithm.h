#ifndef ALGORITHM_H
#define ALGORITHM_H

// Standard Library
#include <memory>

// Backlash Library
#include "AIComponent.h"

namespace backlash {
    class AIComponent;

    class Algorithm {
    public:
        Algorithm(AIComponent *);

        virtual ~Algorithm(); // Probably create this, just in case.

        virtual void Action(double) = 0; 

    protected:
        AIComponent* mCompParent;

    // private:
    //     Algorithm() {}
    };
}

#endif