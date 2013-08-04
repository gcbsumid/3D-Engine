#include "AIComponent.h"

namespace backlash {
    AIComponent::AIComponent() :
        Component(E_COMPONENT::E_COMPONENT_AI), 
        mAlgorithm(NULL) {}

    AIComponent::~AIComponent() {
        if (mAlgorithm) 
            delete mAlgorithm;
    }

    void AIComponent::Update() {
        if (mAlgorithm) {
            mAlgorithm->Action();
        }
    }

    bool AIComponent::Render(Program* shader) {
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
                mAlgorithm = new RotateAlg(mAlgorithm);
                break;
            case E_ALGORITHM::E_ALGORITHM_TRANSLATE:
                mAlgorithm = new Algorithm(mAlgorithm);
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