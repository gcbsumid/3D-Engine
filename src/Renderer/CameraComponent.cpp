// Standard Library 
#include <cassert>
#include <iostream>
#include <string>

// Backlash Library 
#include "CameraComponent.h"
#include "../Util/defines.h"

static void display_vec3(const std::string& title, const glm::vec3& vec) {
    std::cout << title ;
    std::cout << "(" << vec.x << "," << vec.y << "," << vec.z << ")" << std::endl;
}

namespace backlash {
    CameraComponent::CameraComponent() : 
        Component(COMPONENT_CAMERA),
        mHorizontalAngle(0.0f),
        mVerticalAngle(0.0f),
        mFieldOfView(50.0f),
        mNearPlane(0.5f),
        mFarPlane(100.0f),
        mViewportAspectRatio(4.0f/3.0f)
        {
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
        camera *= glm::translate(glm::mat4(), -Position());

        auto modelAttrib = mAttrib.lock();
        modelAttrib->mTransform = camera;
    }

    bool CameraComponent::Render(Program* shader) {
        GLint cameraMatrix = shader->Uniform("camera");
        GLint cameraPosition = shader->Uniform("cameraPosition");

        // std::cout << "cameraMatrix: " << cameraMatrix << std::endl;
        // std::cout << "cameraPosition: " << cameraPosition << std::endl;
        if (cameraMatrix == -1 || 
            cameraPosition == -1) {
            return false;
        }
        // glm::mat4 matrix = Matrix();
        // std::cout << "Camera Transform: " << std::endl;
        // std::cout << "\t{ " << matrix[0][0] << " ,\t" << matrix[0][1] << " ,\t" << matrix[0][2] << " ,\t" <<matrix[0][3] << "}" << std::endl;
        // std::cout << "\t{ " << matrix[1][0] << " ,\t" << matrix[1][1] << " ,\t" << matrix[1][2] << " ,\t" <<matrix[1][3] << "}" << std::endl;
        // std::cout << "\t{ " << matrix[2][0] << " ,\t" << matrix[2][1] << " ,\t" << matrix[2][2] << " ,\t" <<matrix[2][3] << "}" << std::endl;
        // std::cout << "\t{ " << matrix[3][0] << " ,\t" << matrix[3][1] << " ,\t" << matrix[3][2] << " ,\t" <<matrix[3][3] << "}" << std::endl;


        glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, glm::value_ptr(Matrix()));

        glm::vec3 pos(Position());
        // std::cout << "Camera Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
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
        display_vec3("Position is now: ", attrib->mPosition);
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
    }

    glm::mat4 CameraComponent::Orientation() const {
        assert(mAttrib.use_count());
        auto attrib = mAttrib.lock();
        // glm::mat4 orientation = glm::mat4_cast(attrib->mOrientation);
        return attrib->mOrientation;
    }

    // glm must be in degrees This is in degrees
    void CameraComponent::OffsetOrientation(float upAngle, float rightAngle) {
        assert(mAttrib.use_count());
        auto attrib = mAttrib.lock();
        // glm::quat offset(glm::vec3(upAngle, rightAngle, 0.0f));
        // attrib->mOrientation = attrib->mOrientation * offset;

        // std::cout << "Orientation: " ;
        // std::cout << "(" << attrib->mOrientation.w << "," << attrib->mOrientation.x << "," << attrib->mOrientation.y << "," << attrib->mOrientation.z << ")" << std::endl;

        mVerticalAngle += upAngle;
        mHorizontalAngle += rightAngle;

        if (mHorizontalAngle < 0.0f) 
            mHorizontalAngle += 360.0f;
        else if (mHorizontalAngle >= 360.0f) 
            mHorizontalAngle -= 360.0f;

        if (mVerticalAngle > 85.0f) 
            mVerticalAngle = 85.0f;
        else if (mVerticalAngle < -85.0f)
            mVerticalAngle = -85.0f;

        // std::cout << "Vertical Angle: " << mVerticalAngle << std::endl;
        // std::cout << "Horizontal Angle: " << mHorizontalAngle << std::endl;

        glm::mat4 orientation;
        orientation = glm::rotate(orientation, mVerticalAngle, glm::vec3(1,0,0));
        orientation = glm::rotate(orientation, mHorizontalAngle, glm::vec3(0,1,0));
        attrib->mOrientation = orientation;
        Update();
    }

    float CameraComponent::ViewportAspectRatio() const {
        return mViewportAspectRatio;
    }

    void CameraComponent::SetViewportAspectRatio(const float viewportAspectRatio) {
        assert(viewportAspectRatio > 0.0f);
        mViewportAspectRatio = viewportAspectRatio;
    }

    glm::vec3 CameraComponent::Forward() const {
        // get the inverse of the current orientation. We multiply it by 
        // (0,0,-1,1) because we want the inverse of the -Z-axis which is 
        // the forward direction
        glm::vec4 forward = glm::inverse(Orientation()) * glm::vec4(0,0,-1,1);
        // display_vec3("forward: ", glm::vec3(forward);
        return glm::vec3(forward);
    }

    glm::vec3 CameraComponent::Right() const {
        // get the inverse of the current orientation. We multiply it by 
        // (1,0,0,1) because we want the inverse of the -X-axis which is 
        // the Right direction
        glm::vec4 right = glm::inverse(Orientation()) * glm::vec4(1,0,0,1);
        // display_vec3("right: ", glm::vec3(right));
        return glm::vec3(right);
    }

    glm::vec3 CameraComponent::Up() const {
        // get the inverse of the current orientation. We multiply it by 
        // (1,0,0,1) because we want the inverse of the -X-axis which is 
        // the Right direction
        // display_vec3("up: ", glm::vec3(up));
        glm::vec4 up = glm::inverse(Orientation()) * glm::vec4(0,1,0,1);
        return glm::vec3(up);
    }

    glm::mat4 CameraComponent::Matrix() {
        assert(mAttrib.use_count());
        auto attrib = mAttrib.lock();
        Update();
        return attrib->mTransform;
    }

    void CameraComponent::MoveCamera(float elapsedTime, glm::vec3 direction) {
        // std::cout << "Elapsed time: " << elapsedTime << std::endl;
        float distance = utility::MOVE_SPEED * elapsedTime;

        glm::vec3 displacement = distance * direction;

        // display_vec3("displacement: ", glm::vec3(displacement));
        OffsetPosition(displacement);
    }

    void CameraComponent::SetModelAttrib(std::shared_ptr<ModelAttrib> model) {
        assert(model.use_count());
        mAttrib = model;
        SetPosition(utility::DEFAULT_POSITION); 
    }
}