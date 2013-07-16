#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "AIComponent.h"

#include <string>
#include <memory>

namespace backlash {
    class Algorithm {
        typedef std::weak_ptr<AIComponent> AICompPtr;
    public:
        Algorithm(AICompPtr);
        Algorithm(AICompPtr, std::shared_ptr<Algorithm>);

        virtual ~Algorithm(); // Probably create this, just in case.

        virtual void Run() = 0; 

    private:
        std::shared_ptr<Algorithm> mChild;
        AICompPtr mCompParent;
    };
}

#endif