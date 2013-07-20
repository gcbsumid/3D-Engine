#include "AIComponent.h"

namespace backlash {
    AIComponent::AIComponent() :
        Component(E_COMPONENT::E_COMPONENT_AI), 
        mAlgorithm(NULL) {}

    AIComponent::~AIComponent() {}

    void AIComponent::Init() {
        // Do Something here?
    }

    void AIComponent::Update() {
        if (mAlgorithm) {
            mAlgorithm->Action();
        }
    }

    bool AIComponent::Render() {
        // There is nothing to be done here
        // I should be here in the first place so return false
        return false;
    }

    void AIComponent::SetModelAttrib(std::shared_ptr<ModelAttrib> model) {
        mModel = model;
    }

    void AIComponent::GenereateAlgorithm(E_ALGORITHM algo) {
        switch (algo) {
            case E_ALGORITHM::E_ALGORITHM_ROTATE: 
                mAlgorithm = shared_ptr<Alogirthm>(new Algorithm(mAlgorithm));
                break;
            case E_ALGORITHM::E_ALGORITHM_TRANSLATE:
                mAlgorithm = shared_ptr<Algorithm>(new Algorithm(mAlgorithm))
                break;
            default: 
                throw std::runtime_error("Invalid Algorithm Generated.");
                break;
        }            
    }

    void AIComponent::ClearAlgorithm() {
        mAlgorithm = NULL;
    }
};