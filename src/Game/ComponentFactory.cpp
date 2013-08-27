// Backlash Library
#include "ComponentFactory.h"
#include "../AI/AIComponent.h"
#include "../Renderer/DrawComponent.h"
#include "../Renderer/CameraComponent.h"
#include "../Renderer/LightComponent.h"

namespace backlash {
    ComponentFactory::~ComponentFactory() {}

    Component* ComponentFactory::CreateComponent(const COMPONENT compType) {
        if (ComponentInit.find(compType) != ComponentInit.end()) {
            return ComponentInit.at(compType)->Create();
        } else {
            return NULL;
        }
    } 

    std::map<COMPONENT, std::unique_ptr<ComponentFactory>> ComponentFactory::ComponentInit;

    ComponentFactoryInitializer::ComponentFactoryInitializer() {
        ComponentFactory::ComponentInit[COMPONENT_DRAW] = 
            std::unique_ptr<DrawComponent::Factory> (new DrawComponent::Factory);
        ComponentFactory::ComponentInit[COMPONENT_AI] = 
            std::unique_ptr<AIComponent::Factory> (new AIComponent::Factory);
        ComponentFactory::ComponentInit[COMPONENT_CAMERA] = 
            std::unique_ptr<CameraComponent::Factory> (new CameraComponent::Factory);
        ComponentFactory::ComponentInit[COMPONENT_LIGHT] = 
            std::unique_ptr<LightComponent::Factory> (new LightComponent::Factory);
    }

    ComponentFactoryInitializer ComponentFactoryInitializer::initializer;
}