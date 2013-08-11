#ifndef ENGINE_H
#define ENGINE_H

// Standard Library
#include <memory>
#include <map>

// Backlash Library
#include "../AI/AIManager.h"
#include "../Input/InputManager.h"
#include "../Renderer/GraphicsManager.h"
#include "../Resource/ResourceManager.h"
#include "Entity.h"
#include "Component.h"

namespace backlash {
    typedef std::map<int,Entity*> ENTITY_LIST;
    
    class Engine {
    public:
        static Engine* GetInstance();

        ~Engine();

        void Run();             // The game loop

        // Figure out a way how to do this better
        Entity* GetEntity(int) const;

    private:
        Engine();

        void CreateManagers();   // happens in the init()
        void LoadObjects();   // should make calls to the resource manager
        void Update(double);    // This should happen in the AI manager

        // Creates different types of entities
        void CreatePlayer();
        void CreateLight();
        void CreateObjects();

        static Engine* mInstance;

        ENTITY_LIST mEntities;

        std::unique_ptr<GraphicsManager> mGraphics;
        std::unique_ptr<InputManager> mInput;
        std::unique_ptr<ResourceManager> mResource;
        std::unique_ptr<AIManager> mAI;

        // Don't implement copy constructors
        Engine(const Engine&);
        void operator=(const Engine&);

    } ;
}

#endif