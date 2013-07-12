#ifndef ENGINE_H
#define ENGINE_H

#include <cassert>
#include <iostream> // maybe
#include <memory>
#include <map>

#include "Entity.h"
#include "ModelAsset.h"
#include "Component.h"

typedef std::map<GLuint,std::shared_ptr<backlash::Component> > COMPONENT_LIST;
typedef std::map<GLuint,std::shared_ptr<backlash::ModelAsset> > ASSET_LIST; 
typedef std::map<GLuint,std::shared_ptr<backlash::Entity> > ENTITY_LIST;

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
        std::shared_ptr<Component> GetComponent(GLuint) const; 
        std::shared_ptr<ModelAsset> GetAsset(GLuint) const;
        std::shared_ptr<Entity> GetEntity(GLuint) const;

    private:
        Engine();

        void LoadAssets();      // Loads Assets
        void CreateSystems();   // Create All Systems
        void CreateObjects();   // Creates all instances
        void Update(double);    // TODO: create an object system which updates all entities

        static std::shared_ptr<Engine> mInstance;

        COMPONENT_LIST mComponents;
        ASSET_LIST mAssets;
        ENTITY_LIST mEntities;

        std::shared_ptr<GraphicsManager> mGraphics;
        std::shared_ptr<InputManager> mInput;

        // Don't implement copy constructors
        Engine(const Engine&);
        void operator=(const Engine&);

    } ;
}

#endif