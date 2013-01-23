// Third party libraries
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

// Standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

// constants
const glm::vec2 SCREEN_SIZE(800, 600);

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
    if(!glfwOpenWindowHint(SCREEN_SIZE.x, SCREEN_SIZE.y, 8, 8, 8, 8, 0, 0, GLFW_WINDOW)){
        throw runtime_error("glfwOpenWindow failed. Can your hardware handle OpenGL 3.2?");
    }

    // initialize GLEW
    if(!GLEW_VERSION_3_2){
        throw runtime_error("OpenGL 3.2 Api is not available.");
    }

    // clean up and exit
    glfwTerminate();

    return EXIT_SUCCESS;
}