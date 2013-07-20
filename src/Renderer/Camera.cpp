#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

// must be less than 90 to avoid gimbal clock
static const float MAX_VERTICAL_ANGLE = 85.0f;
static const float MOVE_SPEED = 10.0f;

backlash::Camera::Camera() :
    mPosition(0.0f, 0.0f, 1.0f), // looking forward
    mHorizontalAngle(0.0f),
    mVerticalAngle(0.0f),
    mFieldOfView(50.0f),
    mNearPlane(0.01f),
    mFarPlane(100.0f),
    mViewportAspectRatio(4.0f/3.0f) {}

backlash::Camera::~Camera() {};

