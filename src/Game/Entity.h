#ifndef ENTITY_H
#define ENTITY_H

// Standard Library
#include <map>
#include <memory>

// Backlash Library
#include "../Util/enum.h"
#include "ModelAttrib.h"

namespace backlash {
    class Entity {
    public:
        Entity();
        ~Entity();

        void AddComponent(E_COMPONENT);
        std::shared_ptr<Component> GetComponent(E_COMPONENT) const;
        int GetID() const;
        std::shared_ptr<ModelAttrib> GetModelAttrib() const;

        void SetDrawComponentModelAttrib();
        void SetAIComponentModelAttrib();

    private:
        std::map<E_COMPONENT,std::shared_ptr<Component> > mComponents;
        int mID;

        std::shared_ptr<ModelAttrib> mModel;

        // TODO: Make Entities have status that will affect what AI Algorithm 
        //       they will run.
    };
}

#endif