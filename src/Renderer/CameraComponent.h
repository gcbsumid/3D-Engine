#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "../Game/Component.h"
#include "../Util/enum.h"
#include "../Game/ModelAttrib.h"
#include "Program.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>

namespace backlash {
    class CameraComponent : public Component {
    friend class ComponentFactoryInitializer;
    friend class Factory;

    CameraComponent(glm::vec2);
    ~CameraComponent();

    class Factory: public ComponentFactory {
    friend class ComponentFactoryInitializer;
    public:
        Component* Create() {
            return new CameraComponent;
        }
    };

    public:
        virtual void Init();
        virtual void Update();
        virtual bool Render(Program*);

        void SetModelAttrib(std::weak_ptr<ModelAttrib>);

        // Position of Camera
        const glm::vec3& Position() const;
        void SetPosition(const glm::vec3& position);
        void OffsetPosition(const glm::vec3& offset);

        // Determines how wide the view of the camera is
        float FieldOfView() const;
        void SetFieldOfView(const float fieldOfView);

        // The closest and farthest visible distance from the camera
        float NearPlane() const;
        float FarPlane() const;
        void SetNearAndFarPlanes(const float nearPlane, const float farPlane);

        // The rotation matrix that determines the direction the camera 
        // is looking.
        glm::mat4 Orientation() const;
        void OffsetOrientation(float upOffset, float rightOffset);

        // The width divided by the height of the screen/window/viewport
        float ViewportAspectRatio() const;
        void SetViewportAspectRatio(const float viewportAspectRatio); 

        // move Camera function
        void MoveCamera(float elapsedTime, glm::vec3 direction);

        // returns the unit vector representing the direction the camera
        // is facing, to the right of the camera, and top of the camera
        glm::vec3 Forward() const;
        glm::vec3 Right() const;
        glm::vec3 Up() const;

        // the combined camear transformation matrix
        glm::mat4 Matrix() const;

    private:
        std::weak_ptr<ModelAttrib> mAttrib;      

        float mHorizontalAngle;
        float mVerticalAngle;
        float mFieldOfView;
        float mNearPlane;
        float mFarPlane;
        float mViewportAspectRatio;
    };
}

#endif