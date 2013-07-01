#include "EntityComponent.h"
#include "util.h"

backlash::EntityComponent::EntityComponent(backlash::E_COMPONENT type) 
                        : mID(utility::GenerateComponentID()), 
                          mType(type) {}

backlash::EntityComponent::~EntityComponent() {}

GLuint backlash::EntityComponent::GetID() const {
    return mID;
}

backlash::E_COMPONENT backlash::EntityComponent::GetType() const {
    return mType;
}