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

const glm::vec3& backlash::Camera::Position() const {
    return mPosition;
}

void backlash::Camera::SetPosition(const glm::vec3& position) {
    mPosition = position;
}

void backlash::Camera::OffsetPosition(const glm::vec3& offset) {
    mPosition += offset;
}

float backlash::Camera::FieldOfView() const {
    return mFieldOfView;
}

void backlash::Camera::SetFieldOfView(const float fieldOfView) {
    assert(fieldOfView > 0.0f & fieldOfView < 180.0f);
    mFieldOfView = fieldOfView;
}

float backlash::Camera::NearPlane() const {
    return mNearPlane;
}

float backlash::Camera::FarPlane() const {
    return mFarPlane;
}

void backlash::Camera::SetNearAndFarPlanes(const float nearPlane, const float farPlane) {
    assert(nearPlane > 0.0f);
    assert(farPlane > nearPlane);
    mNearPlane = nearPlane;
    mFarPlane = farPlane;
}

glm::mat4 backlash::Camera::Orientation() const {
    glm::mat4 orientation;
    orientation = glm::rotate(orientation, mVerticalAngle, glm::vec3(1,0,0));
    orientation = glm::rotate(orientation, mHorizontalAngle, glm::vec3(0,1,0));
    return orientation;
}

void backlash::Camera::OffsetOrientation(float upAngle, float rightAngle) {
    mHorizontalAngle += rightAngle;
    if(mHorizontalAngle > 360.0f) mHorizontalAngle -= 360;
    if(mHorizontalAngle < 0.0f) mHorizontalAngle += 360;

    mVerticalAngle += upAngle;
    if(mVerticalAngle > MAX_VERTICAL_ANGLE) mVerticalAngle = MAX_VERTICAL_ANGLE;
    if(mVerticalAngle < -MAX_VERTICAL_ANGLE) mVerticalAngle = -MAX_VERTICAL_ANGLE;
}

float backlash::Camera::ViewportAspectRatio() const {
    return mViewportAspectRatio;
}

void backlash::Camera::SetViewportAspectRatio(const float viewportAspectRatio) {
    assert(viewportAspectRatio > 0.0f);
    mViewportAspectRatio = viewportAspectRatio;
}

glm::vec3 backlash::Camera::Forward() const {
    // get the inverse of the current orientation. We multiply it by 
    // (0,0,-1,1) because we want the inverse of the -Z-axis which is 
    // the forward direction
    glm::vec4 forward = glm::inverse(Orientation()) * glm::vec4(0,0,-1,1);
    return glm::vec3(forward);
}

glm::vec3 backlash::Camera::Right() const {
    // get the inverse of the current orientation. We multiply it by 
    // (1,0,0,1) because we want the inverse of the -X-axis which is 
    // the Right direction
    glm::vec4 right = glm::inverse(Orientation()) * glm::vec4(1,0,0,1);
    return glm::vec3(right);
}

glm::vec3 backlash::Camera::Up() const {
    // get the inverse of the current orientation. We multiply it by 
    // (1,0,0,1) because we want the inverse of the -X-axis which is 
    // the Right direction
    glm::vec4 up = glm::inverse(Orientation()) * glm::vec4(0,1,0,1);
    return glm::vec3(up);
}

glm::mat4 backlash::Camera::Matrix() const {
    // we get the orientation and then we multiply it by the negative
    // position because we want to move the world in the oposite direction.
    glm::mat4 camera = glm::perspective(mFieldOfView, mViewportAspectRatio, mNearPlane, mFarPlane);
    camera *= Orientation();
    camera = glm::translate(camera, -mPosition);
    return camera;
}

void backlash::Camera::MoveCamera(float elapsedTime, glm::vec3 direction) {
    float distance = MOVE_SPEED * elapsedTime;

    glm::vec3 displacement = distance * direction;
    OffsetPosition(displacement);
}