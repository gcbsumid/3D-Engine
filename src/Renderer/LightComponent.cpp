#include "LightComponent.h"
#include <GL/glew.h>

#define CHECKINVALID(a) ((a==INVALID_UNIFORM_LOCATION) ? true : false ;)

namespace backlash {
    LightComponent::LightComponent() : 
            Component(E_COMPONENT::E_COMPONENT_LIGHT) {}

    LightComponent::~LightComponent() {}

    void LightComponent::Update() {
        // Do something?
    }

    bool LightComponent::Render(Program* shader) {
        GLuint shaderLoc = shader->Object();
        GLuint position = glGetUniformLocation(shaderLoc,"light.position");
        GLuint intensities = glGetUniformLocation(shaderLoc,"light.intensities");
        GLuint attenuation = glGetUniformLocation(shaderLoc,"light.attenuation");
        GLuint ambientCoefficient= glGetUniformLocation(shaderLoc,"light.ambientCoefficient");

        assert(CHECKINVALID(position));
        assert(CHECKINVALID(intensities));
        assert(CHECKINVALID(attenuation));
        assert(CHECKINVALID(ambientCoefficient));

        glUniform3f(position, mPosition.x, mPosition.y, mPosition.z);
        glUniform3f(intensities, mIntensity.x, mIntensity.y, mIntensity.z);
        glUniform1f(attenuation, mAttenuation);
        glUniform1f(ambientCoefficient, mAmbientCoefficient);
        return true;
    }

    void LightComponent::SetPosition(glm::vec3 position) {
        mPosition = position;
    }

    glm::vec3 LightComponent::GetPosition() const {
        return mPosition;
    }

    void LightComponent::SetIntensity(glm::vec3 intensity) {
        mIntensity = intensity;
    }

    glm::vec3 LightComponent::GetIntensity() const {
        return mIntensity;
    }

    void LightComponent::SetAttenuation(GLfloat attenuation) {
        mAttenuation = attenuation;
    }

    GLfloat LightComponent::GetAttenuation() const {
        return mAttenuation;
    }

    void LightComponent::SetAmbientCoefficient(GLfloat ambientCoefficient) {
        mAmbientCoefficient = ambientCoefficient;
    }

    GLfloat LightComponent::GetAmbientCoefficient() const {
        return mAmbientCoefficient;
    }
}