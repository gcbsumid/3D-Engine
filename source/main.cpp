// Third party libraries
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <string>

// for PATH_MAX
#include <limits>
// for dirname
#include <libgen.h>
// for readlink
#include <unistd.h>

#include "Program.h"
#include "Texture.h"
#include "Camera.h"
#include "util.h"

// std containers
#include <list>

using namespace std;

// constants
const glm::vec2 SCREEN_SIZE(800, 600);

// Structs

/* Note: because the shaders and textures can be shared, you should probably 
 *       store them, later on, inside a std::map and use their ID as what is 
 *       contained inside the ModelAsset.
 */

struct ModelAsset {
    // Material data
    backlash::Program* mShaders;    // the program
    backlash::Texture* mTextures;   // textures

    // Mesh data
    GLuint mVBO;                    // vertex buffer object id; 
    GLuint mVAO;                    // vertex array object id
    // The following are parameters to glDrawArrays
    GLenum mDrawType;
    GLint mDrawStart;
    GLint mDrawCount;

    ModelAsset() : mShaders(NULL),
                   mTextures(NULL),
                   mVBO(0),
                   mVAO(0),
                   mDrawType(GL_TRIANGLES),
                   mDrawStart(0),
                   mDrawCount(0) {} 

    ~ModelAsset() {
        delete mShaders;
        delete mTextures;
    }
} ;

struct ModelInstance {
    ModelAsset* mAsset;
    glm::mat4 mTransform;   // contains size, position, and rotation. 
                            // a.k.a. the model matrix
} ;

// globals 
ModelAsset* gWoodenCrate = NULL;
std::list<ModelInstance> gInstances;

backlash::Camera* gCamera = new backlash::Camera();
GLfloat gDegreesRotated = 0.0f;
const int FPS = 60;

static inline glm::mat4 translate(GLfloat x, GLfloat y, GLfloat z) {
    return glm::translate(glm::mat4(), glm::vec3(x,y,z));
}

static inline glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z) {
    return glm::scale(glm::mat4(), glm::vec3(x,y,z));
}

static backlash::Program* LoadShaders(const string vertex, const string fragment) {
    vector<backlash::Shader> shaders;

    shaders.push_back(backlash::Shader::ShaderFromFile(
        utility::ResourcePath(vertex), 
        GL_VERTEX_SHADER));
    shaders.push_back(backlash::Shader::ShaderFromFile(
        utility::ResourcePath(fragment), 
        GL_FRAGMENT_SHADER));
    return (new backlash::Program(shaders));
}

static void LoadTriangle() {
    // make and bind the VAO 
    glGenVertexArrays(1, &gWoodenCrate->mVAO);
    glBindVertexArray(gWoodenCrate->mVAO);

    // make and bind the VBO
    glGenBuffers(1, &gWoodenCrate->mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gWoodenCrate->mVBO);

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
    GLuint vertAttrib = gWoodenCrate->mShaders->Attrib("vert");
    glEnableVertexAttribArray(vertAttrib);
    glVertexAttribPointer(vertAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    
    // connect the uv coordinates to the "vertTexCoord" attribute of the vertex shader
    GLuint vertTexCoordAttrib = gWoodenCrate->mShaders->Attrib("vertTexCoord");
    glEnableVertexAttribArray(vertTexCoordAttrib);
    glVertexAttribPointer(vertTexCoordAttrib, 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static backlash::Texture* LoadTexture(const string texture) {
    backlash::Bitmap bmp = backlash::Bitmap::BitmapFromFile(utility::ResourcePath(texture));
    bmp.FlipVertically();
    return (new backlash::Texture(bmp));
}

// draws an model instance
static void RenderInstance(const ModelInstance& inst) {
    ModelAsset* asset = inst.mAsset;
    backlash::Program* shaders = asset->mShaders;

    // set shader uniforms
    shaders->SetUniform("camera", gCamera->Matrix());
    shaders->SetUniform("model", inst.mTransform);
    shaders->SetUniform("tex", 0); // texture is bounded to GL_TEXTURE0

    // bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, asset->mTextures->Object());

    /* Note: Consider using glDrawArraysInstanced instead
     *       of glDrawArrays. You can get better performance.
     */
    // bind VAO and draw 
    glBindVertexArray(asset->mVAO);
    glDrawArrays(asset->mDrawType, asset->mDrawStart, asset->mDrawCount);

    // unbind everything
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

// draws a single frame
static void Render() {
    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // render all instances
    backlash::Program* current = NULL;
    for (auto it : gInstances) {
        if (!it.mAsset->mShaders->IsInUse()) {
            if (current && current->IsInUse()) {
                current->Stop();
            }
            current = (it).mAsset->mShaders;
            current->Use();
        }
        RenderInstance(it);
    }
    current->Stop();

    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers();
}

static void Update(double elapsedTime) {
    // Rotate by 1 degree and mod it by 360
    const float degreesPerSecond = 180.0f;
    // rotates 1 degree every 10 pixels or 0.1 degree every pixel.
    const float mouseSensitivity = 0.1f;
    // increases or decreases the field of view
    const float zoomSensitivity = 5.0f;

    // rotating the dot
    gDegreesRotated += elapsedTime * degreesPerSecond;
    while (gDegreesRotated > 360.0f) {
        gDegreesRotated -=360.0f;
    }
    gInstances.front().mTransform = glm::rotate(glm::mat4(), gDegreesRotated, glm::vec3(0,1,0));

    // static float distancePerSecond = 5.0f;
    // if(gTranslateDest.x > 1) {
    //     distancePerSecond = -5.0f;
    // } else if(gTranslateDest.x < -1.0f) {
    //     distancePerSecond = 5.0f;
    // }

    // gTranslateDest += glm::vec3(distancePerSecond*elapsedTime,0,0);



    // move position based on wasd keys
    if (glfwGetKey('S')) {
        gCamera->MoveCamera(elapsedTime, -gCamera->Forward());
    } else if (glfwGetKey('W')) {
        gCamera->MoveCamera(elapsedTime, gCamera->Forward());
    }

    if (glfwGetKey('A')){
        gCamera->MoveCamera(elapsedTime, -gCamera->Right());
    } else if (glfwGetKey('D')){
        gCamera->MoveCamera(elapsedTime, gCamera->Right());
    }

    if (glfwGetKey('X')){
        gCamera->MoveCamera(elapsedTime, -gCamera->Up());
    } else if (glfwGetKey('Z')){
        gCamera->MoveCamera(elapsedTime, gCamera->Up());
    }

    // View rotation based on mouse movements
    int mouseX = 0, mouseY = 0;
    glfwGetMousePos(&mouseX, &mouseY);
    gCamera->OffsetOrientation(mouseSensitivity * mouseY, mouseSensitivity * mouseX);
    glfwSetMousePos(0,0);

    float fieldOfView = gCamera->FieldOfView() + zoomSensitivity * (float)glfwGetMouseWheel();
    if (fieldOfView < 5.0f) {
        fieldOfView = 5.0f;
    }
    if (fieldOfView > 130.0f) {
        fieldOfView = 130.0f;
    }
    gCamera->SetFieldOfView(fieldOfView);
    glfwSetMouseWheel(0);
}

// Loading the wooden crate asset
static void LoadWoodenCrateAsset() {
    gWoodenCrate = new ModelAsset();
    gWoodenCrate->mShaders = LoadShaders("vertex-shader.vert", "fragment-shader.frag");
    gWoodenCrate->mDrawType = GL_TRIANGLES;
    gWoodenCrate->mDrawStart = 0;
    gWoodenCrate->mDrawCount = 6*2*3;
    gWoodenCrate->mTextures = LoadTexture("wooden-crate.jpg");
    glGenBuffers(1, &gWoodenCrate->mVBO);
    glGenVertexArrays(1, &gWoodenCrate->mVAO);
}

static void CreateInstances() {
    ModelInstance dot; 
    dot.mAsset = gWoodenCrate;
    dot.mTransform = glm::mat4();
    gInstances.push_back(dot);

    ModelInstance i; 
    i.mAsset = gWoodenCrate;
    i.mTransform = translate(0,-4,0) * scale(1,2,1);
    gInstances.push_back(i);

    ModelInstance hLeft; 
    hLeft.mAsset = gWoodenCrate;
    hLeft.mTransform = translate(-8,0,0) * scale(1,6,1);
    gInstances.push_back(hLeft);

    ModelInstance hRight; 
    hRight.mAsset = gWoodenCrate;
    hRight.mTransform = translate(-4,0,0) * scale(1,6,1);
    gInstances.push_back(hRight);

    ModelInstance hMid; 
    hMid.mAsset = gWoodenCrate;
    hMid.mTransform = translate(-6,0,0) * scale(2,1,0.8);
    gInstances.push_back(hMid);
}

int main(int argc, char* argv[]) {
    // Initialize GLFW
    if (!glfwInit()) {
        throw runtime_error("glfwInit failed.");
    }

    // open a window in GLFW
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    if (!glfwOpenWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, 8, 8, 8, 8, 16, 0, GLFW_WINDOW)){
        throw runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 3.3?");
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
        throw runtime_error("OpenGL 3.3 Api is not available.");
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Set the camera variables;
    gCamera->SetPosition(glm::vec3(0,0,4));
    gCamera->SetViewportAspectRatio(SCREEN_SIZE.x/SCREEN_SIZE.y);

    LoadWoodenCrateAsset();

    CreateInstances();

    // create buffer and fill it with the points of the triangle
    LoadTriangle();

    // run while the window is open
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
            Render();
        }

        lastFrame = currentTime;

        // HIT escape to escape
        if (glfwGetKey(GLFW_KEY_ESC)) 
            glfwCloseWindow();
    }

    // clean up and exit
    glfwTerminate();

    return EXIT_SUCCESS;
}