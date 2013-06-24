#include "EntityComponent.h"
#include "util.h"

backlash::EntityComponent::EntityComponent() : mID(utility::GenerateComponentID()) {}

backlash::EntityComponent::~EntityComponent() {}

GLuint backlash::EntityComponent::GetID() {
    return mID;
}