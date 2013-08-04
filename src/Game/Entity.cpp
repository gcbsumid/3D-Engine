// Standard C++ Libraries
#include <stdexcept> // Do I need this?
#include <sstream>
#include <cassert>

// Backlash Library
#include "Entity.h"
#include "../Util/util.h"
#include "ComponentFactory.h"
#include "Component.h"
#include "LightComponent.h"
#include "DrawComponent.h"
#include "AIComponent.h"
#include "CameraComponent.h"

extern bool IsValidComponent(backlash::E_COMPONENT comp);
extern bool IsValidAlgorithm(backlash::E_ALGORITHM comp);

namespace backlash {
    Entity::Entity() : mID(utility::GenerateEntityID()), mModel(nullptr) {
        mModel = std::shared_ptr<ModelAttrib>(new ModelAttrib);
        mModel->mTransform = glm::mat4();
        mModel->mPosition = glm::vec3();
        mModel->mOrientation = glm::quat();
    }

    Entity::~Entity() {}

    void Entity::AddComponent(E_COMPONENT type) {
        assert(IsValidComponent(type));
        assert(comp);

        Component* comp = ComponentFactory::CreateComponent(type);

        if (mComponents.count(type)) {
            std::cout << "I'm replacing a Component: " << as_integer(type) << std::endl;
            mComponents[type] = std::shared_ptr<Component>(comp);
        } else {
            mComponents.insert(std::make_pair(type, std::shared_ptr<Component>(comp));
        }

        if (type == E_COMPONENT::E_COMPONENT::DRAW) {
            SetDrawComponentModelAttrib();
        } else if (type == E_COMPONENT::E_COMPONENT_AI) {
            SetAIComponentModelAttrib();
        }
    }

    void Entity::SetDrawComponentModelAttrib() {
        if (mComponents.at(E_COMPONENT::E_COMPONENT_DRAW)) 
            mComponents.at(E_COMPONENT::E_COMPONENT_DRAW)->SetModelAttrib(mModel->get());
    }

    void Entity::SetAIComponentModelAttrib() {
        if (mComponents.at(E_COMPONENT::E_COMPONENT_AI)) 
            mComponents.at(E_COMPONENT::E_COMPONENT_AI)->SetModelAttrib(mModel->get());
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

    std::shared_ptr<ModelAttrib> GetModelAttrib() const {
        return mModel;
    }
}
