#include "AIManager.h"
#include "../Util/util.h"

std::shareD_ptr<backlash::AIManager> backlash::AIManager::mInstance;

namespace backlash {
    AIManager::AIManagerPtr AIManager::GetInstance(AIManager::EnginePtr parent) {
        if (mInstance.get() == 0) {
            mInstance = std::shared_ptr<AIManager>(new AIManager(parent));
        }
        return mInstance;
    }

    AIManager::AIManager(AIManager::EnginePtr parent) :
        mParent(parent) {}
    
    AIManager::~AIManager() {}

    void AIManager::AddAIComponent(std::shared_ptr<AIComponent> comp) {
        utility::IsValidComponent(comp->GetID());
        mComponents.push_back(comp); 
    }

    void AIManager::UpdateAll() {
        // I haven't created states yet so this is empty.
    }

    void AIManager::Run() {
        for (auto comp : mComponents) {
            comp->Run();
        }
    }
}
