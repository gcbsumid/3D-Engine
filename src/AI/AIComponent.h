#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "AlgorithmFactory.h"
#include "Component.h"
#include "enum.h"

#include <vector> 
#include <memory>

// TODO: AIComponent.cpp - implement AIComponent and the Factories

namespace backlash {
    enum class E_ALGORITHMS;

    class AIComponent : public Component {
    public:
        AIComponent(GLuint);
        ~AIComponent();

        void Update(); // TODO: will pass in the status to determine which 
                       //       algorithm will be used.

        void GenerateAlgorithm(E_ALGORITHMS);

    private: 
        std::vector<AIAlgorithms> mAlgorithms;

    };
}

#endif