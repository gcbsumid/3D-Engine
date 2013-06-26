#ifndef UTILITY_H
#define UTILITY_H


// 3rd party libraries
#include <GL/glew.h>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>

#include "Program.h"
// #include "Texture.h"

namespace utility {

    // utility functions
    std::string ResourcePath(std::string filename);
    GLuint GenerateComponentID();
    GLuint GenerateAssetID();
    GLuint GenerateEntityID();
    bool IsValidComponentID(GLuint id);
    bool IsValidAssetID(GLuint id);
    bool IsValidEntityID(GLuint id);
    unsigned long now();

}

#endif