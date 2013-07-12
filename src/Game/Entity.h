#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>

// Standard C++ libraries
#include <map>

#include "enum.h"

namespace backlash {

    class Entity {
    public:
        Entity();
        ~Entity();

        void AddComponent(E_COMPONENT, GLuint);
        GLuint GetComponentID(E_COMPONENT) const;
        GLuint GetID() const;
 
    private:
        std::map<E_COMPONENT,GLuint> mComponents;
        GLuint mID;
        // TODO: Make Entities have a static boolean. Optimization for 
        //       Entity updates.
        // TODO: Make Entities have status that will affect what AI Algorithm 
        //       they will run.
    };
}

#endif