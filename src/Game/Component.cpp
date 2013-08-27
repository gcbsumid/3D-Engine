// Standard Library
#include <iostream>

// Backlash Library
#include "Component.h"
#include "../Util/util.h"

namespace backlash {
	backlash::Component::Component(backlash::COMPONENT type) 
        : mID(utility::GenerateComponentID()), 
          mType(type) {
        std::cout << type << " Component was created." << std::endl;
    }

    backlash::Component::~Component() {}

    int backlash::Component::GetID() const {
        return mID;
    }

    backlash::COMPONENT backlash::Component::GetType() const {
        return mType;
    }
}
