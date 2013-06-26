#include "Engine.h"

namespace backlash {
    Engine::Engine() {
        // TODO: this part.
    }

    void Engine::LoadAssets() {
        // TODO: load the shaders, textures, and mesh data for each asset.
        //       Currently, it should only load WoodenCrate asset
    }

    void Engine::CreateSystems() {
        // TODO: Create the Graphics System and the Input System
    }

    void Engine::CreateObjects() {
        // TODO: Create the Object Instances or Entities. When creating each 
        //       entity, add their respective draw components to the Graphics System
    }

    void Engine::Init() {
        // TODO: Call LoadAssets(), Createsystems(), and CreateObjects()
        //       When creating the CameraComponent, attach it to both the Graphics
        //       system and the Input System
    }
    
    void Engine::Update() {
        // TODO: This basically updates all the entities that need to move. Maybe only go 
        //       through the entities that aren't marked static. 
    }
    
    void Engine::Run() {
        // TODO: This basically contains the gameloop.
    }
}