// Third party libraries
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Standard C++ libraries
#include <memory>
#include <stdexcept>
#include <iostream>

// backlash libraries
#include "Engine.h"

using namespace std;

int main(int argc, char* argv[]) {
    unique_ptr<backlash::Engine> engine(nullptr);
    try {
        engine = unique_ptr<backlash::Engine> (backlash::Engine::GetInstance());
    } catch (exception& err) {
        cout << err.what() << endl;
    }

    if (engine) 
        engine->Run();
    
    return EXIT_SUCCESS;
}