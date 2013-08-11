// Standard Library 
#include <cassert>

// Backlash Library 
#include "CameraComponent.h"
#include "../Util/defines.h"

namespace backlash {
    CameraComponent::CameraComponent() : Component(E_COMPONENT_CAMERA) {
        SetPosition(utility::DEFAULT_POSITION);
        SetViewportAspectRatio(utility::SCREEN_SIZE.x/utility::SCREEN_SIZE.y);
        SetNearAndFarPlanes(utility::DEFAULT_NEAR_PLANE, utility::DEFAULT_FAR_PLANE);
    }
        
    CameraComponent::~CameraComponent() {} 

    void CameraComponent::Update() {
        // we get the orientation and then we multiply it by the negative
        // position because we want to move the world in the oposite direction.
        assert(mAttrib.use_count());
        glm::mat4 camera = glm::perspective(mFieldOfView, mViewportAspectRatio, mNearPlane, mFarPlane);
        camera *= Orientation();
        camera = glm::translate(camera, -Position());

        auto modelAttrib = mAttrib.lock();
        modelAttrib->mTransform = camera;
    }

    bool CameraComponent::Render(Program* shader) {
        GLuint shaderLoc = shader->Object();
        GLuint cameraMatrix = glGetUniformLocation(shaderLoc, "camera");
        GLuint cameraPosition = glGetUniformLocation(shaderLoc, "cameraPosition");

        if (cameraMatrix == INVALID_UNIFORM_LOCATION || 
            cameraPosition == INVALID_UNIFORM_LOCATION) {
            return false;
        }

        glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, glm::value_ptr(Matrix()));

        glm::vec3 pos(Position());
        glUniform3f(cameraPosition, pos.x, pos.y, pos.z);
        return true;
    }

    const glm::vec3& CameraComponent::Position() const {
        assert(mAttrib.use_count());
        auto attrib = mAttrib.lock();
        return attrib->mPosition;
    }

    void CameraComponent::SetPosition(const glm::vec3& position) {
        assert(mAttrib.use_count());
        auto attrib = mAttrib.lock();
        attrib->mPosition = position;
    }

    void CameraComponent::OffsetPosition(const glm::vec3& offset) {
        assert(mAttrib.use_count());
        auto attrib = mAttrib.lock();
        attrib->mPosition += offset;
        Update();
    }

    float CameraComponent::FieldOfView() const {
        return mFieldOfView;
    }

    void CameraComponent::SetFieldOfView(const float fieldOfView) {
        assert(fieldOfView > 0.0f & fieldOfView < 180.0f);
        mFieldOfView = fieldOfView;
        Update();
    }

    float CameraComponent::NearPlane() const {
        return mNearPlane;
    }

    float CameraComponent::FarPlane() const {
        return mFarPlane;
    }

    void CameraComponent::SetNearAndFarPlanes(const float nearPlane, const float farPlane) {
        assert(nearPlane > 0.0f);
        assert(farPlane > nearPlane);
        mNearPlane = nearPlane;
        mFarPlane = farPlane;
        Update();
    }

    glm::mat4 CameraComponent::Orientation() const {
        assert(mAttrib.use_count());
        auto attrib = mAttrib.lock();
        // glm::mat4 orientation = glm::mat4_cast(mAttrib->mOrientation);
        glm::mat4 orientation = glm::mat4_cast(attrib->mOrientation);
        return orientation;
    }

    // glm must be in degrees This is in degrees
    void CameraComponent::OffsetOrientation(float upAngle, float rightAngle) {
        assert(mAttrib.use_count());
        auto attrib = mAttrib.lock();
        glm::quat offset(glm::vec3(upAngle, rightAngle, 0.0f));
        attrib->mOrientation = attrib->mOrientation * offset;
        Update();
    }

    float CameraComponent::ViewportAspectRatio() const {
        return mViewportAspectRatio;
    }

    void CameraComponent::SetViewportAspectRatio(const float viewportAspectRatio) {
        assert(viewportAspectRatio > 0.0f);
        mViewportAspectRatio = viewportAspectRatio;
        Update();
    }

    glm::vec3 CameraComponent::Forward() const {
        // get the inverse of the current orientation. We multiply it by 
        // (0,0,-1,1) because we want the inverse of the -Z-axis which is 
        // the forward direction
        glm::vec4 forward = glm::inverse(Orientation()) * glm::vec4(0,0,-1,1);
        return glm::vec3(forward);
    }

    glm::vec3 CameraComponent::Right() const {
        // get the inverse of the current orientation. We multiply it by 
        // (1,0,0,1) because we want the inverse of the -X-axis which is 
        // the Right direction
        glm::vec4 right = glm::inverse(Orientation()) * glm::vec4(1,0,0,1);
        return glm::vec3(right);
    }

    glm::vec3 CameraComponent::Up() const {
        // get the inverse of the current orientation. We multiply it by 
        // (1,0,0,1) because we want the inverse of the -X-axis which is 
        // the Right direction
        glm::vec4 up = glm::inverse(Orientation()) * glm::vec4(0,1,0,1);
        return glm::vec3(up);
    }

    glm::mat4 CameraComponent::Matrix() const {
        assert(mAttrib.use_count());
        auto attrib = mAttrib.lock();
        return attrib->mTransform;
    }

    void CameraComponent::MoveCamera(float elapsedTime, glm::vec3 direction) {
        float distance = utility::MOVE_SPEED * elapsedTime;

        glm::vec3 displacement = distance * direction;
        OffsetPosition(displacement);
    }

    void CameraComponent::SetModelAttrib(std::shared_ptr<ModelAttrib> model) {
        assert(model.use_count());
        mAttrib = model;
    }
}