#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>

// Standard C++ libraries
#include <map>

#include "enum.h"
#include "ModelAttrib.h"

namespace backlash {
    class Entity {
    public:
        Entity();
        ~Entity();

        void AddComponent(E_COMPONENT, int);
        int GetComponentID(E_COMPONENT) const;
        int GetID() const;
        int GetModelAttrib();

    private:
        std::map<E_COMPONENT,int> mComponents;
        int mID;

        std::shared_ptr<ModelAttrib> mAttrib;
        // TODO: Make Entities have a static boolean. Optimization for 
        //       Entity updates.
        // TODO: Make Entities have status that will affect what AI Algorithm 
        //       they will run.
    };
}

#endif