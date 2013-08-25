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
#include "../Util/defines.h"
#include "Engine.h"
#include "ComponentFactory.h"

namespace backlash {
    // Global static pointer used to ensure my singleton
    Engine* Engine::mInstance{nullptr};

    Engine* Engine::GetInstance() {
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
        if (!glfwOpenWindow(utility::SCREEN_SIZE.x, utility::SCREEN_SIZE.y, 8, 8, 8, 8, 16, 0, GLFW_WINDOW))
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
        // glFrontFace(GL_CW);
        glCullFace(GL_CULL_FACE);
        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);

        CreateManagers();
        LoadObjects();
    }

    Engine::~Engine() {
        for (auto& it : mEntities) {
            delete it.second;
        }
    }

    void Engine::CreateManagers() {
        mGraphics = std::unique_ptr<GraphicsManager>{GraphicsManager::GetInstance()};
        mInput = std::unique_ptr<InputManager>{InputManager::GetInstance()};
        mResource = std::unique_ptr<ResourceManager>{ResourceManager::GetInstance()};
        mAI = std::unique_ptr<AIManager>{AIManager::GetInstance()};

        mGraphics->LoadShaders();

        // Create the Texture and Mesh containers
        std::shared_ptr<std::map<std::string, Texture*>> textures {
            new std::map<std::string, Texture*>, 
            [](std::map<std::string, Texture*>* textures_map){
                for (auto& it : *textures_map) {
                    delete it.second;
                }
            }
        };

        std::shared_ptr<std::map<int, std::shared_ptr<Mesh>>> meshes {
            new std::map<int, std::shared_ptr<Mesh>>,
            [](std::map<int, std::shared_ptr<Mesh>>* meshes_map) {
                for (auto& it : *meshes_map) {
                    it.second.reset();
                }
            }
        };

        mGraphics->SetTextureSharedPointer(textures); // Note: Pass a destructor 
        mGraphics->SetMeshSharedPointer(meshes);
        mResource->SetTextureSharedPointer(textures);
        mResource->SetMeshSharedPointer(meshes);

        mResource->LoadAllFiles();
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
        Entity* player = new Entity;
        player->AddComponent(E_COMPONENT_CAMERA);

        player->SetCameraComponentModelAttrib();

        // Add the camera component to the player entity and systems
        std::shared_ptr<CameraComponent> comp = std::static_pointer_cast<CameraComponent>(player->GetComponent(E_COMPONENT_CAMERA));

        mGraphics->AddCameraComponent(comp);
        mInput->AddCameraComponent(comp);

        // Add player entity to Entity List 
        mEntities.insert(std::make_pair(player->GetID(), player));
    }

    void Engine::CreateLight() {
        Entity* light = new Entity;
        light->AddComponent(E_COMPONENT_LIGHT);

        std::shared_ptr<LightComponent> comp = std::static_pointer_cast<LightComponent>(light->GetComponent(E_COMPONENT_LIGHT));
        comp->SetPosition(glm::vec3(-4,0,4));
        comp->SetIntensity(glm::vec3(1,1,1));
        comp->SetAttenuation(0.2f);
        comp->SetAmbientCoefficient(1.0f);

        // Attach the light to the systems
        mGraphics->AddLightComponent(comp);
        mInput->AddLightComponent(comp);

        mEntities.insert(std::make_pair(light->GetID(), light));
        
    }

    void Engine::CreateObjects() {
        mGraphics->LoadCube();

        Entity* human = new Entity;

        human->AddComponent(E_COMPONENT_AI);
        human->AddComponent(E_COMPONENT_DRAW);

        std::shared_ptr<DrawComponent> drawComp = std::static_pointer_cast<DrawComponent>(human->GetComponent(E_COMPONENT_DRAW));
        std::shared_ptr<AIComponent> aiComp = std::static_pointer_cast<AIComponent>(human->GetComponent(E_COMPONENT_AI));

        human->SetDrawComponentModelAttrib();
        human->SetAIComponentModelAttrib();

        // Generate the AI Algorithm
        aiComp->GenerateAlgorithm(E_ALGORITHM::E_ALGORITHM_ROTATE);

        // Attach Shader and Mesh to the component
        mGraphics->AttachShaderToDrawComponent(drawComp.get(), 0); 
        mGraphics->AttachMeshToDrawComponent(drawComp.get(), 0);

        // Attach the Components to their respective managers
        mGraphics->AddDrawComponent(drawComp);
        mAI->AddAIComponent(aiComp);
        
        mEntities.insert(std::make_pair(human->GetID(), human));
    }

    void Engine::Update(double timeTick) {
        // Deal with the input
        mInput->HandleInput(timeTick);

        // Deal with updating the status of each AI component and then running them
        mAI->UpdateAll();
        mAI->Action(timeTick);
    }
    
    void Engine::Run() {
        auto lastFrame= std::chrono::high_resolution_clock::now();

        while(glfwGetWindowParam(GLFW_OPENED)) {
            auto currentTime = std::chrono::high_resolution_clock::now();

            // Update animations (note: if anything, cast this to double)
            Update(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFrame).count() / 1000.0f); 

            mGraphics->Render();

            if (glfwGetKey(GLFW_KEY_ESC)) 
                glfwCloseWindow();

            lastFrame = currentTime;   
        }

        // clean up and exits 
        glfwTerminate();
    }

    Entity* Engine::GetEntity(int id) const {
        assert(utility::IsValidEntityID(id));

        return mEntities.at(id);
    }
}