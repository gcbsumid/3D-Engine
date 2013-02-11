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
#include "util.h"

using namespace std;

// constants
const glm::vec2 SCREEN_SIZE(800, 600);

// globals 
mogl::Program* gProgram = NULL;
mogl::Texture* gTexture = NULL;
GLfloat gDegreesRotated = 0.0f;
glm::vec3 gTranslateDest = glm::vec3(0,0,0); 
GLuint gVAO = 0;
GLuint gVBO = 0;
const int FPS = 60;


static void LoadShaders() {
    vector<mogl::Shader> shaders;
    // std::cout << ResourcePath("source/vertex-shader.txt") << std::endl;
    // std::cout << ResourcePath("source/fragment-shader.txt") << std::endl;

    shaders.push_back(mogl::Shader::ShaderFromFile(
        utility::ResourcePath("vertex-shader.vert"), 
        GL_VERTEX_SHADER));
    shaders.push_back(mogl::Shader::ShaderFromFile(
        utility::ResourcePath("fragment-shader.frag"), 
        GL_FRAGMENT_SHADER));
    gProgram = new mogl::Program(shaders);

    gProgram->Use();

    // set the camera matrix
    glm::mat4 camera = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    gProgram->SetUniform("camera", camera);

    // set the projection matrix 
    glm::mat4 projection = glm::perspective<float>(50.0, SCREEN_SIZE.x/SCREEN_SIZE.y, 0.1, 10.0);
    gProgram->SetUniform("projection", projection);

    gProgram->Stop();
}

// loads a triangle into the VAO and globals: gVAO and gVBO
static void LoadTriangle() {
    // make and bind the VAO 
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    // make and bind the VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

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
    GLuint vertAttrib = gProgram->Attrib("vert");
    glEnableVertexAttribArray(vertAttrib);
    glVertexAttribPointer(vertAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    
    // connect the uv coordinates to the "vertTexCoord" attribute of the vertex shader
    GLuint vertTexCoordAttrib = gProgram->Attrib("vertTexCoord");
    glEnableVertexAttribArray(vertTexCoordAttrib);
    glVertexAttribPointer(vertTexCoordAttrib, 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

    // unbind the VBO and VAO
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// loads the file "hazard.png" into gTexture
static void LoadTexture() {
    mogl::Bitmap bmp = mogl::Bitmap::BitmapFromFile(utility::ResourcePath("wooden-crate.jpg"));
    bmp.FlipVertically();
    gTexture = new mogl::Texture(bmp);
}

// draws a single frame
static void Render() {
    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind the program (the shaders)
    gProgram->Use();

    // set the model matrix
    glm::mat4 rot = glm::rotate(glm::mat4(), gDegreesRotated, glm::vec3(0,1,0));
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(2,0,0));
    // glm::mat4 trans = glm::translate(glm::mat4(1.0f), gTranslateDest);
    gProgram->SetUniform("model", rot * trans);

    // bind the texture and set the "tex" uniform in the fragment
    // shader
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture->Object());
    gProgram->SetUniform("tex", 0);

    // bind the VAO (the triangle)
    glBindVertexArray(gVAO);

    // draw the VAO
    glDrawArrays(GL_TRIANGLES, 0, 3*6*2);

    // unbind the VAO, the program and the texture
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    gProgram->Stop();

    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers();
}

static void Update(double elapsedTime) {
    // Rotate by 1 degree and mod it by 360
    const float degreesPerSecond = 180.0f;
    // static float distancePerSecond = 5.0f;
    gDegreesRotated += elapsedTime * degreesPerSecond;
    // if(gTranslateDest.x > 1) {
    //     distancePerSecond = -5.0f;
    // } else if(gTranslateDest.x < -1.0f) {
    //     distancePerSecond = 5.0f;
    // }

    // gTranslateDest += glm::vec3(distancePerSecond*elapsedTime,0,0);

    if(gDegreesRotated >= 360) {
        gDegreesRotated -= 360.0f;
    }
}

int main(int argc, char* argv[]) {
    // Initialize GLFW
    if(!glfwInit()){
        throw runtime_error("glfwInit failed.");
    }

    // open a window in GLFW
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    if(!glfwOpenWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, 8, 8, 8, 8, 16, 0, GLFW_WINDOW)){
        throw runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 3.2?");
    }

    // initialise GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // initialize GLEW
    if(!GLEW_VERSION_3_2){
        throw runtime_error("OpenGL 3.2 Api is not available.");
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Loading vertext and fragment shaders into opengl
    LoadShaders();

    // load the texture
    LoadTexture();

    // create buffer and fill it with the points of the triangle
    LoadTriangle();

    // run while the window is open
    double lastFrame= glfwGetTime();
    int framePerSecond = 0;
    double timer = 0.0f;
    double frameTimer = 0.0f;
    while(glfwGetWindowParam(GLFW_OPENED)) {
        // draw one frame
        double currentTime = glfwGetTime();

        timer += currentTime - lastFrame;
        frameTimer += currentTime - lastFrame;

        // // Frame Rate Counter
        // if(frameTimer > 1.0f) {
        //     std::cout << "Frames Per Second: " << framePerSecond << std::endl;
        //     frameTimer -= 1.0f;
        //     framePerSecond = 0;
        // }

        // Update animations
        Update(currentTime - lastFrame);

        // Controlling frame rate to 60 fps
        if(timer > 1.0/60.0) {
            framePerSecond++;
            timer -= 1.0/60.0;
            Render();
        }

        lastFrame = glfwGetTime();
    }

    // clean up and exit
    glfwTerminate();

    return EXIT_SUCCESS;
}