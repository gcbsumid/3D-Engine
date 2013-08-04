// GL and GLM Libraries
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glfw.h>

// Standard Library
#include <chrono>
#include <string>

// Backlash Library
#include "../Renderer/Texture.h"
#include "../Renderer/DrawComponent.h"
#include "../Renderer/CameraComponent.h"
#include "../Renderer/LightComponent.h"
#include "../Util/util.h"
#include "../Util/enum.h"
#include "Engine.h"
#include "ComponentFactory.h"

namespace backlash {
    // Global static pointer used to ensure my singleton
    Engine* Engine::mInstance{nullptr};

    std::shared_ptr<Engine> Engine::GetInstance() {
        if (mInstance == nullptr)
            mInstance = new Engine;

        return mInstance;
    }

    Engine::Engine() : mGraphics(nullptr), 
                       mInput(nullptr),
                       mResource(nullptr),
                       mAI(nullptr) 
                       {
        // Initialize GLFW
        if (!glfwInit()) 
            throw std::runtime_error("glfwInit failed.");

        // open a window in GLFW
        glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
        glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
        glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
        if (!glfwOpenWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, 8, 8, 8, 8, 16, 0, GLFW_WINDOW))
            throw std::runtime_error("glfwOpenWindow failed. Hardware can't handle OpenGL 3.3");

        // initialise GLEW
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
            throw std::runtime_error("glewInit failed");

        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

        // GLFW settings
        glfwDisable(GLFW_MOUSE_CURSOR);
        glfwSetMousePos(0,0);
        glfwSetMouseWheel(0);

        // initialize GLEW
        if (!GLEW_VERSION_3_3) 
            throw std::runtime_error("OpenGL 3.3 Api is not available.");

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        CreateManagers();
        LoadObjects();
    }

    void Engine::CreateManagers() {
        mGraphics = std::unique_ptr<GraphicsManager>{GraphicsManager::GetInstance(mInstance)};
        mInput = std::unique_ptr<InputManager>{InputManager::GetInstance(mInstance)};
        mResource = std::unique_ptr<ResourceManager>{ResourceManager::GetInstance(mInstance)};
        mAI = std::unique_ptr<AIManager>{AIManager::GetInstance(mInstance)};

        // Create the Texture and Mesh containers
        std::map<std::string, Texture*>* textures = new std::map<std::string, Texture*>;
        std::vector<Mesh>* meshes = new std::vector<Mesh>;
        mGraphics->SetTextureSharedPointer(textures);
        mGraphics->SetMeshSharedPointer(meshes);
        mInput->SetTextureSharedPointer(textures);
        mInput->SetMeshSharedPointer(meshes);

        mResourceManager->LoadAllFiles();
    }

    void Engine::LoadObjects() {
        // TODO: maybe create a file that contains these information and have the engine read 
        //       it and create the objects based on the information. Maybe create a LoadScene() 
        //       function that reads and parses the file

        CreatePlayer();
        CreateLight();
        CreateObjects();
    }

    void Engine::CreatePlayer() {
        // Set up the camera
        CameraComponent* cameraComp = ComponentFactory::CreateComponent(E_COMPONENT::E_COMPONENT_CAMERA);

        Entity* player = new Entity;
        player->AddComponent(E_COMPONENT::E_COMPONENT_CAMERA, cameraComp);
        player->SetDrawComponentModelAttrib();

        // Add the camera component to the player entity and systems
        mGraphics->AddCameraComponent(cameraComponent);
        mInput->AddCameraComponent(cameraComponent);

        // Add player entity to Entity List 
        mEntities.insert(std::make_pair(player->GetID(), player));
    }

    void Engine::CreateLight() {
        Entity* light = new Entity;
        LightComponent* lightComponent = ComponentFactory::CreateComponent(E_COMPONENT::E_COMPONENT_LIGHT);
        light->AddComponent(E_COMPONENT::E_COMPONENT_LIGHT, lightComponent);
        mGraphics->AddLightComponent(lightComponent);
        mInput->AddLightComponent(lightComponent);
        mEntities.insert(std::make_pair(light->GetID(), light));
        lightComponent->SetPosition(glm::vec3(0,3,3));
        lightComponent->SetIntensity(glm::vec3(1,1,1));
        lightComponent->SetAttenuation(0.1f);
        lightComponent->SetAmbientCoefficient(0.005f);
    }

    void Engine::CreateObjects() {
        Entity* human = new Entity;
        DrawComponent* drawComponent = ComponentFactory::CreateComponent(E_COMPONENT::E_COMPONENT_DRAW);
        AIComponent* aiComponent = ComponentFactory::CreateComponent(E_COMPONENT::E_COMPONENT_AI);

        human->AddComponent(E_COMPONENT::E_COMPONENT_DRAW, drawComponent);
        human->AddComponent(E_COMPONENT::E_COMPONENT_AI, aiComponent);
        human->SetDrawComponentModelAttrib();
        human->SetAIComponentModelAttrib();

        // currently, I only have one shader program. It's ID is 0.
        mGraphics->AttachShaderToDrawComponent(drawComponent, 0); 

        // After loading human 
        mGraphics->AttachMeshToDrawComponent(drawComponent, "Human");

        // Generate the AI Algorithm
        aiComponent->GenerateAlgorithm(E_ALGORITHM::E_ALGORITHM_ROTATE);

        mEntities.insert(std::make_pair(human->GetID(), human));
    }

    void Engine::Update(double timeTick) {
        // Deal with the input
        mInput->HandleInput(elapsedTime);

        // Deal with updating the status of each AI component and then running them
        mAI->UpdateAll();
        mAI->Run(timeTick);
    }
    
    void Engine::Run() {
        double lastFrame= std::chrono::high_resolution_clock::now();

        while(glfwGetWindowParam(GLFW_OPENED)) {
            double currentTime = std::chrono::high_resolution_clock::now();

            // Update animations (note: if anything, cast this to double)
            Update(std::chrono::duration_cast<seconds>(currentTime - lastFrame).count()); 

            mGraphics->Render();

            lastFrame = currentTime;

            if (glfwGetKey(GLFW_KEY_ESC)) 
                glfwCloseWindow();
        }

        // clean up and exits 
        glfwTerminate();
    }

    std::shared_ptr<Entity> Engine::GetEntity(GLuint id) const {
        assert(utility::IsValidEntityID(id));

        return mEntities.at(id);
    }
}