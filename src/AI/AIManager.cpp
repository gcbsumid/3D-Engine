#include "AIManager.h"

backlash::AIManager* backlash::AIManager::mInstance{nullptr};

namespace backlash {
    AIManager* AIManager::GetInstance() {
        if (!mInstance) {
            mInstance = new AIManager;
        }
        return mInstance;
    }

    AIManager::AIManager() {}
    
    AIManager::~AIManager() {}

    void AIManager::AddAIComponent(std::shared_ptr<AIComponent> comp) {
        assert(comp.use_count());
        mComponents.push_back(std::weak_ptr<AIComponent>(comp)); 
    }

    void AIManager::UpdateAll() {
        for (auto& comp : mComponents) {
            if (comp.use_count()) {
                comp->Update(timeTick);
            } else {
                mComponents.erase(comp);
            }
        }
    }

    void AIManager::Action(double timeTick) {
        for (auto& comp : mComponents) {
            if (comp.use_count()) {
                comp->Action(timeTick);
            }
        }
    }
}
