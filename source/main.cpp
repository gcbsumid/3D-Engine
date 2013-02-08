// Third party libraries
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

// Standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <string>
#include <sys/time.h>

// for PATH_MAX
#include <limits>
// for dirname
#include <libgen.h>
// for readlink
#include <unistd.h>

#include "Program.h"

using namespace std;

// constants
const glm::vec2 SCREEN_SIZE(800, 600);

// globals 
mogl::Program* gProgram = NULL;
GLuint gVAO = 0;
GLuint gVBO = 0;
const int FPS = 30;

static unsigned long now() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

static string ResourcePath(string fileName){
    // Gets the full directory of the program on linux
    char exe_file[PATH_MAX + 1];
    int size;
    size = readlink("/proc/self/exe", exe_file, PATH_MAX);
    if (size < 0) {
        return ".//../"+ fileName;
    } else {
        exe_file[size] = '\0';
        // dirname reports the parent directory of a file
        return string(dirname(exe_file)) + "//../" + fileName;
    }
}

static void LoadShaders() {
    vector<mogl::Shader> shaders;
    // std::cout << ResourcePath("source/vertex-shader.txt") << std::endl;
    // std::cout << ResourcePath("source/fragment-shader.txt") << std::endl;

    shaders.push_back(mogl::Shader::ShaderFromFile(
        ResourcePath("resource/vertex-shader.vert"), 
        GL_VERTEX_SHADER));
    shaders.push_back(mogl::Shader::ShaderFromFile(
        ResourcePath("resource/fragment-shader.frag"), 
        GL_FRAGMENT_SHADER));
    gProgram = new mogl::Program(shaders);
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
        // X    Y   Z
        0.0f, 0.8f, 0.0f,
       -0.8f,-0.8f, 0.0f,
        0.8f,-0.8f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // connect the xyz to the "vert" attribute of the vertex shader 
    GLuint attrib = gProgram->Attrib("vert");
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// draws a single frame
static void Render() {
    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind the program (the shaders)
    glUseProgram(gProgram->Object());

    // bind the VAO (the triangle)
    glBindVertexArray(gVAO);

    // draw the VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // unbind the VAO
    glBindVertexArray(0);

    // unbind the program
    glUseProgram(0);

    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers();
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
    if(!glfwOpenWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, 8, 8, 8, 8, 0, 0, GLFW_WINDOW)){
        throw runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 3.2?");
    }

    // initialise GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // initialize GLEW
    if(!GLEW_VERSION_3_2){
        throw runtime_error("OpenGL 3.2 Api is not available.");
    }

    // Loading vertext and fragment shaders into opengl
    LoadShaders();

    // create buffer and fill it with the points of the triangle
    LoadTriangle();

    // run while the window is open
    unsigned long lastRepaint= 0;
    while(glfwGetWindowParam(GLFW_OPENED)) {
        // draw one frame
        unsigned long end = now();
        if(end - lastRepaint > 1000000/FPS) {
            Render();
            lastRepaint = now();
        } else {
            usleep(1000000/FPS - (end - lastRepaint));
        }
    }

    // clean up and exit
    glfwTerminate();

    return EXIT_SUCCESS;
}