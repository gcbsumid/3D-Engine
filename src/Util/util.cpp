#include <sys/time.h>
#include <string>

// for PATH_MAX
#include <limits>
// for dirname
#include <libgen.h>
// for readlink
#include <unistd.h>

#include "util.h"

static GLuint CURRENT_COMPONENT_ID = 0;
static GLuint CURRENT_ASSET_ID = 0;
static GLuint CURRENT_ENTITY_ID = 0;

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
        return std::string(dirname(exe_file)) + "/../resource/" + fileName;
    }
}

unsigned long utility::now() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

GLuint utility::GenerateComponentID() {
    return CURRENT_COMPONENT_ID++;
}

GLuint utility::GenerateAssetID() {
    return CURRENT_ASSET_ID++;
}

GLuint utility::GenerateEntityID() {
    return CURRENT_ENTITY_ID++;
}

bool utility::IsValidComponentID(GLuint id) {
    return (id < CURRENT_COMPONENT_ID) ? true : false;
}

bool utility::IsValidAssetID(GLuint id) {
    return (id < CURRENT_ASSET_ID) ? true : false;
}

bool utility::IsValidEntityID(GLuint id) {
    return (id < CURRENT_ENTITY_ID) ? true : false;
}