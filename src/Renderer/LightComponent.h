#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

#include "Component.h"
#include "enum.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace backlash {
    class LightComponent : public Component {
    public:
        LightComponent();
        ~LightComponent();

        void Update();

        void SetPosition(glm::vec3);
        glm::vec3 GetPosition() const;

        void SetIntensity(glm::vec3);
        glm::vec3 GetIntensity() const;

        void SetAttenuation(GLfloat);
        GLfloat GetAttenuation() const;

        void SetAmbientCoefficient(GLfloat);
        GLfloat GetAmbientCoefficient() const;
    private:
        glm::vec3 mPosition;
        glm::vec3 mIntensity;
        GLfloat mAttenuation; 
        GLfloat mAmbientCoefficient;
    };
}

#endif