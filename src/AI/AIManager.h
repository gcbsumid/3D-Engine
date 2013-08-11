#ifndef AIMANAGER_H
#define AIMANAGER_H

// Standard Library
#include <vector> // Probably for the Algorithms to update.
#include <memory>

// Backlash Library
#include "AIComponent.h"


namespace backlash {
    class Engine;

    class AIManager {
    public:
        static AIManager* GetInstance();
        ~AIManager();

        // Prereq: Install the xml parser and create objects
        // TODO: When you create the entire game using an xml file, dynamically
        //       create the Algorithms to be attached to the individual 
        //       AI components by passing an object of some sort that contains
        //       the needed data from the xml file 
        void AddAIComponent(std::shared_ptr<AIComponent> comp);

        // TODO: Create states to which each object will be updated
        void UpdateAll();

        void Action(double);

    private:
        AIManager();

        std::vector<std::weak_ptr<AIComponent>> mComponents;

        static AIManager* mInstance;

        // Don't Implement the copy constructors
        AIManager(const AIManager&);
        void operator=(const AIManager&);
    };
}

#endif 