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
        for (auto it = mComponents.begin(); it != mComponents.end(); ++it) {
            if (auto comp = it->lock()) {
                comp->Update();
            } else {
                mComponents.erase(it);
            }
        }
    }

    void AIManager::Action(double timeTick) {
        for (auto& it : mComponents) {
            if (auto comp = it.lock()) {
                comp->Action(timeTick);
            }
        }
    }
}
