#include "Engine.h"
#include "Program.h"
#include "Texture.h"
#include "util.h"
#include <GL/glfw.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

// for PATH_MAX
#include <limits>
// for dirname
#include <libgen.h>
// for readlink
#include <unistd.h>


// constants
const glm::vec2 SCREEN_SIZE(800, 600);
static const float degreesPerSecond = 180.0f;

// Global static pointer used to ensure my singleton
std::shared_ptr<backlash::Engine> backlash::Engine::mInstance;

// THIS IS ONLY TEMPORARY
GLuint gDotID = -1;
GLfloat tempGDegreesRotated = 0.0f;

static inline glm::mat4 translate(GLfloat x, GLfloat y, GLfloat z) {
    return glm::translate(glm::mat4(), glm::vec3(x,y,z));
}

static inline glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z) {
    return glm::scale(glm::mat4(), glm::vec3(x,y,z));
}

static void LoadTriangle(std::shared_ptr<backlash::ModelAsset> asset) {
    // make and bind the VAO 
    glGenVertexArrays(1, &asset->mVAO);
    glBindVertexArray(asset->mVAO);

    // make and bind the VBO
    glGenBuffers(1, &asset->mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, asset->mVBO);

    // Put the three triangle vertices into the VBO
    GLfloat vertexData[] = {
    //      X     Y     Z       U     V
    // bottom
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,

    // top
        -1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

    // front
        -1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

    // back
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
        1.0f, 1.0f,-1.0f,   1.0f, 1.0f,

    // left
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
        -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,   1.0f, 0.0f,

    // right
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
        1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
        1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // connect the xyz to the "vert" attribute of the vertex shader 
    GLuint vertAttrib = asset->mShaders->Attrib("vert");
    glEnableVertexAttribArray(vertAttrib);
    glVertexAttribPointer(vertAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    
    // connect the uv coordinates to the "vertTexCoord" attribute of the vertex shader
    GLuint vertTexCoordAttrib = asset->mShaders->Attrib("vertTexCoord");
    glEnableVertexAttribArray(vertTexCoordAttrib);
    glVertexAttribPointer(vertTexCoordAttrib, 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static std::shared_ptr<backlash::Program> LoadShaders(const std::string vertex, const std::string fragment) {
    std::vector<backlash::Shader> shaders;

    shaders.push_back(backlash::Shader::ShaderFromFile(
        utility::ResourcePath(vertex), 
        GL_VERTEX_SHADER));
    shaders.push_back(backlash::Shader::ShaderFromFile(
        utility::ResourcePath(fragment), 
        GL_FRAGMENT_SHADER));
    return std::shared_ptr<backlash::Program>(new backlash::Program(shaders));
}

static std::shared_ptr<backlash::Texture> LoadTexture(const std::string texture) {
    backlash::Bitmap bmp = backlash::Bitmap::BitmapFromFile(utility::ResourcePath(texture));
    bmp.FlipVertically();
    return std::shared_ptr<backlash::Texture>(new backlash::Texture(bmp));
}

namespace backlash {
    Engine::Engine() : mGraphics(NULL), mInput(NULL) {
    }

    
    std::shared_ptr<Engine> Engine::GetInstance() {
        if (mInstance.use_count() < 1) {
            mInstance = std::shared_ptr<Engine>(new Engine);
        }

        return mInstance;
    }

    void Engine::LoadAssets() {
        std::shared_ptr<ModelAsset> woodenCrate(new ModelAsset());
        mAssets.insert(std::make_pair(woodenCrate->mID, woodenCrate));

        LoadTriangle(woodenCrate);

        woodenCrate->mShaders = LoadShaders("vertex-shader.vert", "fragment-shader.frag");
        woodenCrate->mDrawType = GL_TRIANGLES;
        woodenCrate->mDrawStart = 0;
        woodenCrate->mDrawCount = 6*2*3;
        woodenCrate->mTextures = LoadTexture("wooden-crate.jpg");
        glGenBuffers(1, &woodenCrate->mVBO);
        glGenVertexArrays(1, &woodenCrate->mVAO);
    }

    void Engine::CreateSystems() {
        mGraphics = GraphicsSystem::GetInstance();
        mInput = InputSystem::GetInstance();

        std::shared_ptr<CameraComponent> cameraComponent(new CameraComponent(SCREEN_SIZE));
        std::shared_ptr<Entity> player(new Entity());

        // Add the camera component to the player entity and systems
        player->AddComponent(E_COMPONENT_CAMERA, cameraComponent->GetID());
        mGraphics->AddCameraComponent(cameraComponent->GetID());
        mInput->AddCameraComponent(cameraComponent->GetID());

        // Add camera component to components list
        mComponents.insert(std::make_pair(cameraComponent->GetID(), cameraComponent));

        // Add player entity to Entity List 
        mEntities.insert(std::make_pair(player->GetID(), player));
    }

    void Engine::CreateObjects() {
        GLuint woodCrateAssetID = 0;

        std::shared_ptr<Entity> dot(new Entity());
        std::shared_ptr<DrawComponent> dotDrawComponent(new DrawComponent(woodCrateAssetID));
        dotDrawComponent->SetTransform(glm::mat4());
        dot->AddComponent(E_COMPONENT_DRAW, dotDrawComponent->GetID());
        mEntities.insert(std::make_pair(dot->GetID(),dot));
        gDotID = dot->GetID();

        std::shared_ptr<Entity> i(new Entity());
        std::shared_ptr<DrawComponent> iDrawComponent(new DrawComponent(woodCrateAssetID));
        iDrawComponent->SetTransform(translate(0,-4,0) * scale(1,2,1));
        i->AddComponent(E_COMPONENT_DRAW, iDrawComponent->GetID());
        mEntities.insert(std::make_pair(i->GetID(),i));

        std::shared_ptr<Entity> hLeft(new Entity());
        std::shared_ptr<DrawComponent> hLeftDrawComponent(new DrawComponent(woodCrateAssetID));
        hLeftDrawComponent->SetTransform(translate(-8,0,0) * scale(1,6,1));
        hLeft->AddComponent(E_COMPONENT_DRAW, hLeftDrawComponent->GetID());
        mEntities.insert(std::make_pair(hLeft->GetID(),hLeft));

        std::shared_ptr<Entity> hRight(new Entity());
        std::shared_ptr<DrawComponent> hRightDrawComponent(new DrawComponent(woodCrateAssetID));
        hRightDrawComponent->SetTransform(translate(-4,0,0) * scale(1,6,1));
        hRight->AddComponent(E_COMPONENT_DRAW, hRightDrawComponent->GetID());
        mEntities.insert(std::make_pair(hRight->GetID(),hRight));

        std::shared_ptr<Entity> hMid(new Entity());
        std::shared_ptr<DrawComponent> hMidDrawComponent(new DrawComponent(woodCrateAssetID));
        hMidDrawComponent->SetTransform(translate(-6,0,0) * scale(2,1,0.8));
        hMid->AddComponent(E_COMPONENT_DRAW, hMidDrawComponent->GetID());
        mEntities.insert(std::make_pair(hMid->GetID(),hMid));
    }

    void Engine::Init() {    
        // Initialize GLFW
        if (!glfwInit()) {
            throw std::runtime_error("glfwInit failed.");
        }

        // open a window in GLFW
        glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
        glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
        glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
        if (!glfwOpenWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, 8, 8, 8, 8, 16, 0, GLFW_WINDOW)){
            throw std::runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 3.3?");
        }

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
        if (!GLEW_VERSION_3_3){
            throw std::runtime_error("OpenGL 3.3 Api is not available.");
        }

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        CreateSystems();
        LoadAssets();
        CreateObjects();
    }
    
    void Engine::Update(double elapsedTime) {
        mInput->HandleInput(mComponents, elapsedTime);

        // rotating the dot
        tempGDegreesRotated += elapsedTime * degreesPerSecond;
        while (tempGDegreesRotated > 360.0f) {
            tempGDegreesRotated -=360.0f;
        }
        GLuint drawComponentID = mEntities.at(gDotID)->GetComponentID(E_COMPONENT_DRAW);
        std::shared_ptr<DrawComponent> dotDrawComp = std::static_pointer_cast<DrawComponent>(mComponents.at(drawComponentID));
        dotDrawComp->SetTransform(glm::rotate(glm::mat4(), tempGDegreesRotated, glm::vec3(0,1,0)));
    }
    
    void Engine::Run() {
        double lastFrame= glfwGetTime();
        int framePerSecond = 0;
        double timer = 0.0f;

        // double frameTimer = 0.0f;
        while(glfwGetWindowParam(GLFW_OPENED)) {
            // draw one frame
            double currentTime = glfwGetTime();

            timer += currentTime - lastFrame;
            // frameTimer += currentTime - lastFrame;

            // // Frame Rate Counter
            // if (frameTimer > 1.0f) {
            //     std::cout << "Frames Per Second: " << framePerSecond << std::endl;
            //     frameTimer -= 1.0f;
            //     framePerSecond = 0;
            // }

            // Update animations
            Update(currentTime - lastFrame);

            // Controlling frame rate to 60 fps
            if (timer > 1.0/60.0) {
                // Update(1.0/60.0);
                framePerSecond++;
                timer -= 1.0/60.0;
                mGraphics->Render(mComponents, mAssets);
            }

            lastFrame = currentTime;

            // HIT escape to escape
            if (glfwGetKey(GLFW_KEY_ESC)) 
                glfwCloseWindow();
        }

        // clean up and exits 
        glfwTerminate();
    }
}