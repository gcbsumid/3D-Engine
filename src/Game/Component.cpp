#include "Component.h"
#include "../Util/util.h"

namespace backlash {
	backlash::Component::Component(backlash::E_COMPONENT type) 
        : mID(utility::GenerateComponentID()), 
          mType(type) {}

    backlash::Component::~Component() {}

    int backlash::Component::GetID() const {
        return mID;
    }

    backlash::E_COMPONENT backlash::Component::GetType() const {
        return mType;
    }
}
