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
        return string(dirname(exe_file)) + "/";
    }
}

static void LoadShaders(mogl::Program* program) {
    vector<mogl::Shader> shaders;
    shaders.push_back(mogl::Shader::shaderFromFile(
        ResourcePath("source/vertex-shader.txt"), 
        GL_VERTEX_SHADER));
    shaders.push_back(mogl::Shader::shaderFromFile(
        ResourcePath("source/fragment-shader.txt"), 
        GL_FRAGMENT_SHADER));
    program = new mogl::Program(shaders);
}

int main(int argc, char* argv[]) {
    // initialize the program object
    mogl::Program* program = NULL;

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
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // initialize GLEW
    if(!GLEW_VERSION_3_2){
        throw runtime_error("OpenGL 3.2 Api is not available.");
    }

    // Loading vertext and fragment shaders into opengl
    LoadShaders(program);

    // clean up and exit
    glfwTerminate();

    return EXIT_SUCCESS;
}