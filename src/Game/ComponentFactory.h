#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "Component.h"
#include "enum.h"

#include <memory>

// TODO: Implement ComponentFactory.cpp. Modify all components to be only 
//       created by the component factories

namespace backlash {
    enum class E_COMPONENT;

    class ComponentFactory {
    public:
        virtual ~ComponentFactory();  
        friend class ComponentFactoryInitializer;

        // Static function so it can be called without an instantiation
        // TODO: do the static pointer cast in this function
        static std::shared_ptr<Component> CreateComponent(E_COMPONENT);

    private:
        virtual Component* create() = 0;
        static std::map<E_ComponentS, ComponentFactory*> CountryInit;
    };

    class ComponentFactoryInitializer {
        static ComponentFactoryInitializer initializer;
        ComponentFactoryInitializer();
        ComponentFactoryInitializer(const ComponentFactoryInitializer&);
    };

}

#endif