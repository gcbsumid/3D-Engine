#pragma once

// 3rd party libraries
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>

#include "Program.h"
// #include "Texture.h"

namespace utility {

    // utility functions
    std::string ResourcePath(std::string filename);
    unsigned long now();
}