#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <sys/time.h>
#include <string>

// for PATH_MAX
#include <limits>
// for dirname
#include <libgen.h>
// for readlink
#include <unistd.h>

#include "util.h"

using namespace utility;

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