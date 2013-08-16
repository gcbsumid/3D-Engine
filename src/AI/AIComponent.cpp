// Standard Library
#include <stdexcept>
#include <iostream>

// Backlash Library
#include "../Util/enum.h"
#include "AIComponent.h"
#include "RotateAlg.h"
#include "TranslateAlg.h"

namespace backlash {
    AIComponent::AIComponent() :
        Component(E_COMPONENT_AI) ,
        mModel()
        {
            // mLocalAlgos.insert(std::make_pair(E_ALGORITHM_ROTATE, new RotateAlg(this)));
        }

    AIComponent::~AIComponent() {
        ClearAlgorithms();
    }

    void AIComponent::Update() {
        // Ideally I'd want to attach a state diagram for this. This is also where 
        // I will end up traversing that state diagram.
    }

    void AIComponent::Action(double timeTick) {
        for (auto& algo : mAlgorithms) {
            algo->Action(timeTick);
        }        
    }

    bool AIComponent::Render(Program* shader) {
        return false;
    }

    void AIComponent::SetModelAttrib(std::shared_ptr<ModelAttrib> model) {
        assert(model.use_count());
        mModel = model;
    }

    void AIComponent::GenerateAlgorithm(E_ALGORITHM type) {
        Algorithm* algo = nullptr;
        switch (type) {
            case E_ALGORITHM::E_ALGORITHM_ROTATE: 
                algo = new RotateAlg(this);
                break;
            case E_ALGORITHM::E_ALGORITHM_TRANSLATE:
                algo = new TranslateAlg(this);
                break;
            default: 
                throw std::runtime_error("Invalid Algorithm Generated.");
                break;
        }           
        mAlgorithms.push_back(std::unique_ptr<Algorithm>(algo));
    }

    void AIComponent::ClearAlgorithms() {
        for (std::vector<std::unique_ptr<Algorithm>>::iterator algo = mAlgorithms.begin(); algo != mAlgorithms.end(); ++algo) {
            (*algo).reset();
            mAlgorithms.erase(algo);
        }
    }
};