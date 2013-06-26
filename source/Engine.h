#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cassert>
#include <iostream> // maybe
#include <memory>
#include <map>
#include <list>

#include "InputSystem.h"
#include "GraphicsSystem.h"
#include "Entity.h"
#include "ModelAsset.h"
#include "EntityComponent.h"
#include "DrawComponent.h"
#include "CameraComponent.h"

typedef std::map<GLuint,std::shared_ptr<backlash::EntityComponent> > COMPONENT_LIST;
typedef std::map<GLuint,std::shared_ptr<backlash::ModelAsset> > ASSET_LIST; 
typedef std::list<std::shared_ptr<Entity> > ENTITY_LIST;

namespace backlash {
    class Engine {
    public:
        static Engine& getInstance() {
            static Engine instance;
            return instance;
        }

        ~Engine();

        void Run();             // The game loop
        void Init();            // Initialize Engine properties

    private:
        Engine();

        void LoadAssets();      // Loads Assets
        void CreateSystems();   // Create All Systems
        void CreateObjects();   // Creates all instances
        void Update(double);    // TODO: create an object system which updates all entities

        COMPONENT_LIST mComponents;
        ASSET_LIST mAssets;
        ENTITY_LIST mEntities;

        GraphicsSystem mGraphics;
        InputSystem mInput;

        // Don't implement copy constructors
        Engine(const Engine&);
        void operator=(const Engine&);

    } ;
}

#endif;