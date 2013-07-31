#ifndef AIMANAGER_H
#define AIMANAGER_H

#include "../Game/Engine.h"
#include "AIComponent.h"

#include <vector> // Probably for the Algorithms to update.
#include <memory>

namespace backlash {
    class Engine;

    class AIManager {
        typedef std::shared_ptr<AIManager> AIManagerPtr; 
        typedef std::weak_ptr<Engine> EnginePtr;

    public:
        static AIManagerPtr GetInstance(EnginePtr);
        ~AIManager();

        // Prereq: Install the xml parser and create objects
        // TODO: When you create the entire game using an xml file, dynamically
        //       create the Algorithms to be attached to the individual 
        //       AI components by passing an object of some sort that contains
        //       the needed data from the xml file 
        void AddAIComponent(AIComponent* comp);

        // This actually updates the algorithms to run depending on the state 
        // of each object
        // TODO: Create states to which each object will be updated
        void UpdateAll();

        // This runs all actions in all the AI Components. This may need to pass an elapsed time
        void Run(double)

    private:
        AIManager(EnginePtr parent);

        const Engine_ptr mParent;
        std::vector<std::weak_ptr<AIComponent> > mComponents;

        // Don't Implement the copy constructors
        AIManager(const AIManager&);
        void operator=(const AIManager&);
    };
}

#endif 