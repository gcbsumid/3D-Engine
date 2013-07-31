#include "ComponentFactory.h"
#include "../AI/AIComponent.h"
#include "../Renderer/DrawComponent.h"
#include "../Renderer/CameraComponent.h"
#include "../Renderer/LightComponent.h"

namespace backlash {
    std::map<E_COMPONENT, std::unique_ptr<ComponentFactory> > ComponentInit;

    ComponentFactory::~ComponentFactory() {
        // Well, I don't really need this since I'm using smart pointers
        for (auto it : ComponentFactory::ComponentInit) {
            it->second.reset();
        }
    }

    Component* ComponentFactory::CreateComponent(E_COMPONENT compType) {
        if (ComponentInit.find(compType)) {
            return ComponentInit.at(compType)->Create();
        } else {
            return NULL;
        }
    } 

    ComponentFactoryInitializer ComponentFactoryInitializer::initializer;

    ComponentFactoryInitializer::ComponentFactoryInitializer() {
        ComponentFactory::CountryInit[E_COMPONENT_DRAW] = 
            std::unique_ptr<DrawComponent> (new DrawComponent);
        ComponentFactory::CountryInit[E_COMPONENT_AI] = 
            std::unique_ptr<AIComponent> (new AIComponent);
        ComponentFactory::CountryInit[E_COMPONENT_CAMERA] = 
            std::unique_ptr<CameraComponent> (new CameraComponent);
        ComponentFactory::CountryInit[E_COMPONENT_LIGHT] = 
            std::unique_ptr<LightComponent> (new LightComponent);
    }
}