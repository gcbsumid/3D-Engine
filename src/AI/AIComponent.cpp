// Standard Library
#include <stdexcept>

// Backlash Library
#include "AIComponent.h"
#include "RotateAlg.h"
#include "TranslateAlg.h"

namespace backlash {
    AIComponent::AIComponent() :
        Component(E_COMPONENT_AI) 
        {}

    AIComponent::~AIComponent() {
        ClearAlgorithms();
    }

    void AIComponent::Update() {
        // Ideally I'd want to attach a state diagram for this. This is also where 
        // I will end up traversing that state diagram.
    }

    void AIComponent::Action(double timeTick) {
        for (auto& algo : mAlgorithms) {
            algo.second->Action(timeTick);
        }        
    }

    bool AIComponent::Render(Program* shader) {
        return false;
    }

    void AIComponent::SetModelAttrib(std::shared_ptr<ModelAttrib> model) {
        mModel = model;
    }

    void AIComponent::GenerateAlgorithm(E_ALGORITHM algo) {
        if (mAlgorithms[algo]) {
            mAlgorithms[algo].reset();
        }
        switch (algo) {
            case E_ALGORITHM::E_ALGORITHM_ROTATE: 
                mAlgorithms[algo] = std::unique_ptr<Algorithm>(new RotateAlg(this));
                break;
            case E_ALGORITHM::E_ALGORITHM_TRANSLATE:
                mAlgorithms[algo] = std::unique_ptr<Algorithm>(new TranslateAlg(this));
                break;
            default: 
                throw std::runtime_error("Invalid Algorithm Generated.");
                break;
        }            
    }

    void AIComponent::ClearAlgorithms() {
        for (auto& algo : mAlgorithms) {
            algo.second.reset();
        }
    }
};