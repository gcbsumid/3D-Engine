#include "Component.h"
#include "util.h"

backlash::Component::Component(backlash::E_COMPONENT type) 
                        : mID(utility::GenerateComponentID()), 
                          mType(type) {}

backlash::Component::~Component() {}

GLuint backlash::Component::GetID() const {
    return mID;
}

backlash::E_COMPONENT backlash::Component::GetType() const {
    return mType;
}