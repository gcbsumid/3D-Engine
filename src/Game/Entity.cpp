// Standard C++ Libraries
#include <stdexcept> // Do I need this?
#include <sstream>
#include <cassert>

// Backlash Library
#include "Entity.h"
#include "../Util/util.h"
#include "../Util/enum.h"
#include "ComponentFactory.h"
#include "Component.h"
#include "../Renderer/LightComponent.h"
#include "../Renderer/DrawComponent.h"
#include "../Renderer/CameraComponent.h"
#include "../AI/AIComponent.h"

namespace backlash {
    Entity::Entity() : mID(utility::GenerateEntityID()), mModel(nullptr) {
        mModel = std::shared_ptr<ModelAttrib>(new ModelAttrib);
        mModel->mTransform = glm::mat4();
        mModel->mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        mModel->mOrientation = glm::mat4();
        mModel->mScale = glm::vec3(0.1f, 0.1f, 0.1f);
    }

    Entity::~Entity() {}

    void Entity::AddComponent(E_COMPONENT type) {
        assert(IsValidComponent(type));

        Component* comp = ComponentFactory::CreateComponent(type);

        if (mComponents.count(type)) {
            std::cout << "I'm replacing a Component: " << type << std::endl;
            mComponents[type] = std::shared_ptr<Component>(comp);
        } else {
            mComponents.insert(std::make_pair(type, std::shared_ptr<Component>(comp)));
        }

        if (type == E_COMPONENT_DRAW) {
            SetDrawComponentModelAttrib();
        } else if (type == E_COMPONENT_AI) {
            SetAIComponentModelAttrib();
        }
    }

    void Entity::SetDrawComponentModelAttrib() {
        if (mComponents.at(E_COMPONENT_DRAW)) {
            std::shared_ptr<DrawComponent> comp = std::static_pointer_cast<DrawComponent>(mComponents.at(E_COMPONENT_DRAW));
            comp->SetModelAttrib(mModel);
        }
    }

    void Entity::SetAIComponentModelAttrib() {
        if (mComponents.at(E_COMPONENT_AI)) {
            std::shared_ptr<AIComponent> comp = std::static_pointer_cast<AIComponent>(mComponents.at(E_COMPONENT_AI));            
            comp->SetModelAttrib(mModel);
        }
    }

    void Entity::SetCameraComponentModelAttrib() {
        if (mComponents.at(E_COMPONENT_CAMERA)) {
            std::shared_ptr<CameraComponent> comp = std::static_pointer_cast<CameraComponent>(mComponents.at(E_COMPONENT_CAMERA));            
            comp->SetModelAttrib(mModel);
        }
    }

    std::shared_ptr<Component> Entity::GetComponent(E_COMPONENT type) const {
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

    std::shared_ptr<ModelAttrib> Entity::GetModelAttrib() const {
        return mModel;
    }

    void Entity::SetPosition(glm::vec3 position) {
        std::cout << "Light Position is now: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

        mModel->mPosition = position;
        mModel->UpdateTransform();
    }

    void Entity::SetScale(glm::vec3 scale) {
        mModel->mPosition = scale;
        mModel->UpdateTransform();
    }

    void Entity::DisplayPosition() {
        glm::vec3 pos = mModel->mPosition;
        std::cout << "Position: (" << pos.x << "," << pos.y << "," << pos.z << ")" << std::endl;
    }

}
