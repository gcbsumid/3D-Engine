#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include <GL/glew.h>

#include "Algorithm.h"
#include "Component.h"
#include "ModelAttrib.h"
#include "enum.h"

#include <vector> 
#include <memory>

// TODO: AIComponent.cpp - implement AIComponent and the Factories

namespace backlash {
    enum class E_ALGORITHM;

    class AIComponent : public Component {
        friend Algorithm;
    public:
        AIComponent(shared_ptr<ModelAttrib>);
        ~AIComponent();

        void Update(); // TODO: will pass in the status to determine which 
                       //       algorithm will be used.

        void GenerateAlgorithm(E_ALGORITHM);
        void ClearAlgorithm();
    private: 
        std::shared_ptr<Algorithm> mAlgorithm; 
        std::shared_ptr<ModelAttrib> mAttrib; 
    };
}

#endif