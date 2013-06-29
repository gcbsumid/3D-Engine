#include "LightComponent.h"

backlash::LightComponent::LightComponent() : backlash::EntityComponent() {}

backlash::LightComponent::~LightComponent() {}

void backlash::LightComponent::Update() {
    // Do something?
}

void backlash::LightComponent::SetPosition(glm::vec3 position) {
    mPosition = position;
}

glm::vec3 backlash::LightComponent::GetPosition() const {
    return mPosition;
}

void backlash::LightComponent::SetIntensity(glm::vec3 intensity) {
    mIntensity = intensity;
}

glm::vec3 backlash::LightComponent::GetIntensity() const {
    return mIntensity;
}