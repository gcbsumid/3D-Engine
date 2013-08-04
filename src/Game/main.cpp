// Third party libraries
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Standard C++ libraries
#include <memory>
#include <stdexcept>

// backlash libraries
#include "Engine.h"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        unique_ptr<backlash::Engine> gEngine{backlash::Engine::GetInstance()};
    } catch (exception& err) {
        cout << err.what() << endl;
    }

    gEngine->Run();
    
    return EXIT_SUCCESS;
}