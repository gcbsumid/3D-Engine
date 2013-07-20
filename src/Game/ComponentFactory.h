#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "Component.h"
#include "enum.h"

#include <memory>
#include <map>

namespace backlash {
    enum class E_COMPONENT;

    class ComponentFactory {
    public:
        virtual ~ComponentFactory();  
        friend class ComponentFactoryInitializer;

        // Static function so it can be called without an instantiation
        // Super inconsistent. shoulda used a shared_ptr but its too much work.
        static Component* CreateComponent(E_COMPONENT);
    private:
        virtual Component* Create() = 0;
        static std::map<E_ComponentS, std::unique_ptr<ComponentFactory> > ComponentInit;
    };

    class ComponentFactoryInitializer {
        static ComponentFactoryInitializer initializer;
        ComponentFactoryInitializer();
        ComponentFactoryInitializer(const ComponentFactoryInitializer&);
    };

}

#endif