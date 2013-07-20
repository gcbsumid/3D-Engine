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

        void AddComponent(E_COMPONENT, std::shared_ptr<Component> comp);
        int GetComponent(E_COMPONENT) const;
        int GetID() const;
        std::shared_ptr<ModelAttrib> GetModelAttrib();

    private:
        std::map<E_COMPONENT,std::shareD_ptr<Component> > mComponents;
        int mID;

        std::shared_ptr<ModelAttrib> mModel;

        // TODO: Make Entities have status that will affect what AI Algorithm 
        //       they will run.
    };
}

#endif