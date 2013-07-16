#include "AIComponent.h"

namespace backlash {
    AIComponent::AIComponent(shared_ptr<ModelAttrib> attrib) :
        Component(E_COMPONENT::E_COMPONENT_AI), 
        mAttrib(attrib),
        mAlgorithm(NULL) {}

    AIComponent::~AIComponent() {}

    void AIComponent::Update() {
        if (mAlgorithm) {
            mAlgorithm->Action();
        }
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