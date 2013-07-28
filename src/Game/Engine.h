#ifndef ENGINE_H
#define ENGINE_H

#include <cassert>
#include <iostream> // maybe
#include <memory>
#include <map>

#include "../AI/AIManager.h"
#include "../Input/InputManager.h"
#include "../Renderer/GraphicsManager.h"
#include "../Resource/ResourceManager.h"

#include "Entity.h"
#include "Component.h"
#include "../Renderer/ModelAsset.h"

// typedef std::map<int,std::shared_ptr<backlash::Component> > COMPONENT_LIST;
// typedef std::map<int,std::shared_ptr<backlash::ModelAsset> > ASSET_LIST; 
typedef std::map<int,std::shared_ptr<backlash::Entity> > ENTITY_LIST;

namespace backlash {
    class GraphicsManager;
    class InputManager;
    
    class Engine {
    public:
        static std::shared_ptr<Engine> GetInstance();

        ~Engine() {}

        void Run();             // The game loop
        void Init();            // Initialize Engine properties

        // Figure out a way how to do this better
        std::shared_ptr<Component> GetComponent(int) const; 
        std::shared_ptr<ModelAsset> GetAsset(int) const;
        std::shared_ptr<Entity> GetEntity(int) const;

    private:
        Engine();

        void LoadAssets();      // Should happen in the resource manager
        void CreateManagers();   // happens in the init()
        void InitManagers();
        void CreateObjects();   // should make calls to the resource manager
        void Update(double);    // This should happen in the AI manager

        static std::shared_ptr<Engine> mInstance;

        // COMPONENT_LIST mComponents;
        // ASSET_LIST mAssets;
        ENTITY_LIST mEntities;

        std::shared_ptr<GraphicsManager> mGraphics;
        std::shared_ptr<InputManager> mInput;
        std::shared_ptr<ResourceManager> mResource;
        std::shared_ptr<AIManager> mAI;

        // Don't implement copy constructors
        Engine(const Engine&);
        void operator=(const Engine&);

    } ;
}

#endif