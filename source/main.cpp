// Third party libraries
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Standard C++ libraries
#include <memory>

#include "Engine.h"
using namespace std;

// Structs

/* Note: because the shaders and textures can be shared, you should probably 
 *       store them, later on, inside a std::map and use their ID as what is 
 *       contained inside the ModelAssetTemp.
 */


int main(int argc, char* argv[]) {
    shared_ptr<backlash::Engine> gEngine = backlash::Engine::GetInstance();

    return EXIT_SUCCESS;
}