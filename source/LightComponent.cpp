#include "LightComponent.h"

namespace backlash {
    LightComponent::LightComponent() : 
            EntityComponent(E_COMPONENT::E_COMPONENT_LIGHT) {}

    LightComponent::~LightComponent() {}

    void LightComponent::Update() {
        // Do something?
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