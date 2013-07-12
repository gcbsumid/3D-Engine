#ifndef ROTATEALG_H
#define ROTATEALG_H

#include "Algorithm.h"
#include "AlgorithmFactory.h"

#include <memory>

// TODO: Implement RotateAlg.cpp and other algorithms

namespace backlash {
    class RotateAlg : public Algorithm {
        friend class AlgorithmFactoryInitializer;
        friend class Factory;

        RotateAlg();
        ~RotateAlg();

        class Factory : public AlgorithmFactory {
            friend class AlgorithmFactoryInitializer;
        
        public:
            Algorithm* creatE() {
                return new RotateAlg();
            }
        };

    public:
        virtual void Update();
    };
}

#endif