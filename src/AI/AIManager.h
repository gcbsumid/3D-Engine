#ifndef AIMANAGER_H
#define AIMANAGER_H

#include "Engine.h"
#include "AIComponent.h"

#include <vector> // Probably for the Algorithms to update.
#include <memory>

// TODO: The .cpp file 

namespace backlash {
    class Engine;

    class AIManager {
        typedef std::shared_ptr<AIManager> AIManagerPtr;
        typedef std::shared_ptr<Engine> EnginePtr;
    public:
        static AIManagerPtr GetInstance(EnginePtr parent);
        ~AIManager();

        void AddAIComponent(std::sharedPtr<AIComponent> comp);

        void UpdateAll();

    private:
        AIManager(EnginePtr parent);

        const Engine_ptr mParent;
        std::vector<AIComponent> mComponents;

        // Don't Implement the copy constructors
        AIManager(const AIManager&);
        void operator=(const AIManager&);
    };
}

#endif 