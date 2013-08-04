#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

// Standard Library
#include <memory>
#include <map>

// Backlash Library
#include "Component.h"
#include "../Util/enum.h"

namespace backlash {
    class ComponentFactory {
    public:
        virtual ~ComponentFactory();  
        friend class ComponentFactoryInitializer;

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