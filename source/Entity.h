#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>

// Standard C++ libraries
#include <map>

namespace backlash {
    enum E_COMPONENT {
        E_COMPONENT_FIRST = 0,
        E_COMPONENT_DRAW = E_COMPONENT_FIRST,
        E_COMPONENT_CAMERA,

        E_COMPONENT_MAX
    } ;

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
    };
}

#endif