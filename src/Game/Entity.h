#ifndef ENTITY_H
#define ENTITY_H

// Standard Library
#include <map>
#include <memory>

// Backlash Library
#include "../Util/enum.h"
#include "Component.h"
#include "ModelAttrib.h"

namespace backlash {
    class Component;

    class Entity {
    public:
        Entity();
        ~Entity();

        void AddComponent(COMPONENT);
        std::shared_ptr<Component> GetComponent(COMPONENT) const;
        int GetID() const;
        std::shared_ptr<ModelAttrib> GetModelAttrib() const;

        void SetDrawComponentModelAttrib();
        void SetAIComponentModelAttrib();
        void SetCameraComponentModelAttrib();
        
        void SetScale(glm::vec3 scale);
        void SetPosition(glm::vec3 position);
        void DisplayPosition();
    private:
        std::map<COMPONENT,std::shared_ptr<Component> > mComponents;
        int mID;

        std::shared_ptr<ModelAttrib> mModel;

        // TODO: Make Entities have status that will affect what AI Algorithm 
        //       they will run.
    };
}

#endif