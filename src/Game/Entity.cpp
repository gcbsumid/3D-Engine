#include "Entity.h"
#include "util.h"

// Standard C++ Libraries
#include <utility> // Do I need this?
#include <stdexcept> // Do I need this?
#include <sstream>
#include <cassert>

static bool IsValid(backlash::E_COMPONENT comp) {
    return (comp >= backlash::E_COMPONENT::E_COMPONENT_DRAW && 
            comp < backlash::E_COMPONENT::E_COMPONENT_MAX) ? true : false;
}

namespace backlash {
    Entity::Entity() : mID(utility::GenerateEntityID()) {
        mModel = std::shared_ptr<ModelAttrib> (new ModelAttrib);
        mModel->mTransform = glm::mat4();
        mModel->mPosition = glm::vec3();
        mModel->mOrientation = glm::quat();
    }

    Entity::~Entity() {}

    void Entity::AddComponent(E_COMPONENT type, std::shared_ptr<Component> comp) {
        assert(IsValid(type));

        if (mComponents.count(type)) {
            mComponents[type] = comp;
        } else {
            mComponents.insert(std::make_pair(type, comp));
        }
    }

    int Entity::GetComponent(E_COMPONENT type) const {
        if (mComponents.count(type) == 0) {
            std::stringstream msg;
            msg << "The component " << (unsigned int)type << " doesn't exist in this entity." << std::endl;
            throw std::runtime_error(msg.str());
        }

        return mComponents.at(type);
    }

    int Entity::GetID() const {
        return mID;
    }

    std::shared_ptr<ModelAttrib> GetModelAttrib() {
        return mModel;
    }
}
