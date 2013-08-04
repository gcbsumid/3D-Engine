#include "AIManager.h"

backlash::AIManager* backlash::AIManager::mInstance{nullptr};

namespace backlash {
    AIManager* AIManager::GetInstance(Engine* parent) {
        assert(parent);
        if (!mInstance) {
            mInstance = new AIManager{parent};
        }
        return mInstance;
    }

    AIManager::AIManager(Engine* parent) :
        mParent{parent} {}
    
    AIManager::~AIManager() {}

    void AIManager::AddAIComponent(AIComponent* comp) {
        assert(comp);
        mComponents.push_back(std::weak_ptr<AIComponent>(comp)); 
    }

    void AIManager::UpdateAll() {
        for (auto& comp : mComponents) {
            comp->Update(timeTick);
        }
    }

    void AIManager::Action(double timeTick) {
        for (auto& comp : mComponents) {
            comp->Action(timeTick);
        }
    }
}
