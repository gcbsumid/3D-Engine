// Standard Libraries
#include <string>

#include <limits>       // for PATH_MAX
#include <libgen.h>     // for dirname
#include <unistd.h>     // for readlink

// Utility Library
#include "util.h"

static int CURRENT_COMPONENT_ID = 0;
static int CURRENT_ASSET_ID = 0;
static int CURRENT_ENTITY_ID = 0;

#define INVALID_OGL_VALUE 0xFFFFFFFF

std::string utility::ResourcePath(std::string fileName){
    // Gets the full directory of the program on linux
    char exe_file[PATH_MAX + 1];
    int size;
    size = readlink("/proc/self/exe", exe_file, PATH_MAX);
    if (size < 0) {
        return "./../"+ fileName;
    } else {
        exe_file[size] = '\0';
        // dirname reports the parent directory of a file
        return std::string(dirname(exe_file)) + "/../assets/" + fileName;
    }
}

int utility::GenerateComponentID() {
    return CURRENT_COMPONENT_ID++;
}

int utility::GenerateAssetID() {
    return CURRENT_ASSET_ID++;
}

int utility::GenerateEntityID() {
    return CURRENT_ENTITY_ID++;
}

bool utility::IsValidComponentID(int id) {
    return (id < CURRENT_COMPONENT_ID) ? true : false;
}

bool utility::IsValidAssetID(int id) {
    return (id < CURRENT_ASSET_ID) ? true : false;
}

bool utility::IsValidEntityID(int id) {
    return (id < CURRENT_ENTITY_ID) ? true : false;
}