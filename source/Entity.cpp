#include "Entity.h"

// Standard C++ Libraries
#include <utility>
#include <stdexcept>
#include <sstream>
#include <cassert>

static bool IsValid(backlash::E_COMPONENT comp) {
    return (comp >= backlash::E_COMPONENT::E_COMPONENT_FIRST && 
            comp < backlash::E_COMPONENT::E_COMPONENT_MAX) ? true : false;
}

backlash::Entity::Entity() {}

backlash::Entity::~Entity() {}

void backlash::Entity::AddComponent(backlash::E_COMPONENT comp, GLuint id) {
    assert(IsValid(comp));

    if (mComponents.count(comp)) {
        mComponents[comp] = id;
    } else {
        mComponents.insert(std::make_pair(comp, id));
    }
}

GLuint backlash::Entity::GetComponentID(E_COMPONENT comp) {
    if (mComponents.count(comp) == 0) {
        std::stringstream msg;
        msg << "The component " << comp << " doesn't exist in this entity." << std::endl;
        throw std::runtime_error(msg.str());
    }

    return mComponents.at(comp);
}