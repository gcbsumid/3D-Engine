// GL Library
#include <GL/glew.h>

// Standard Library 
#include <cassert>
#include <iostream>

// Backlash Library
#include "LightComponent.h"
#include "../Util/defines.h"

namespace backlash {
    LightComponent::LightComponent() : 
            Component(COMPONENT_LIGHT) {}

    LightComponent::~LightComponent() {}

    void LightComponent::Update() {
        // Do something?
    }

    bool LightComponent::Render(Program* shader) {
        GLint position = shader->Uniform("light.position");
        GLint intensities = shader->Uniform("light.intensities");
        GLint attenuation = shader->Uniform("light.attenuation");
        GLint ambientCoefficient= shader->Uniform("light.ambientCoefficient");

        // std::cout << "position: " << position << std::endl;
        // std::cout << "intensities: " << intensities << std::endl;
        // std::cout << "attenuation: " << attenuation << std::endl;
        // std::cout << "ambientCoefficient: " << ambientCoefficient << std::endl;

        // std::cout << "Light Position: " << "(" << mPosition.x << "," << mPosition.y << "," << mPosition.z << ")" << std::endl;
        // std::cout << "Light Intensity: " << "(" << mIntensity.x << "," << mIntensity.y << "," << mIntensity.z << ")" << std::endl;
        // std::cout << "Light Attenuation: " << mAttenuation << std::endl;
        // std::cout << "Light Ambient Coefficient: " << mAmbientCoefficient << std::endl;

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