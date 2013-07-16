#ifndef UTILITY_H
#define UTILITY_H

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>

#include "Program.h"
// #include "Texture.h"

namespace utility {
    // utility functions
    std::string ResourcePath(std::string filename);
    int GenerateComponentID();
    int GenerateAssetID();
    int GenerateEntityID();
    bool IsValidComponentID(int id);
    bool IsValidAssetID(int id);
    bool IsValidEntityID(int id);
    unsigned long now();

}

#endif