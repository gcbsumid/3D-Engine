#ifndef DEFINES_H
#define DEFINES_H

// Glm Library
#include <glm/glm.hpp>

#define INVALID_UNIFORM_LOCATION 0xFFFFFFFF
#define INVALID_OGL_VALUE 0xFFFFFFFF

#define CHECKINVALID(a) (a==-1) ? false : true

namespace utility {

    const glm::vec2 SCREEN_SIZE(800, 600);
    const glm::vec3 DEFAULT_POSITION(-4,0,17);
    const float     DEFAULT_NEAR_PLANE = 0.5f;
    const float     DEFAULT_FAR_PLANE = 150.0f;
    const float     MOUSE_SENSITIVITY = 0.01f;
    const float     ZOOM_SENSITIVITY = 5.0f;
    const float     MOVE_SPEED = 5.0f;
}

#endif