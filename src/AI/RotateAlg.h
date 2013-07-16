#ifndef ROTATEALG_H
#define ROTATEALG_H

#include "Algorithm.h"

#include <memory>

// TODO: Implement RotateAlg.cpp and other algorithms

namespace backlash {
    class RotateAlg : public Algorithm {
    public:
        RotateAlg(Algorithm::AICompPtr comp);
        RotateAlg(Algorithm::AICompPtr comp, shared_ptr<Algorithm>);

        ~RotateAlg();
        
        virtual void Run();
    };
}

#endif