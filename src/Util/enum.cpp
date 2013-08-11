#include "enum.h"

namespace backlash {
    bool IsValidComponent(E_COMPONENT comp) {
        return (comp >= E_COMPONENT::E_COMPONENT_DRAW && 
                comp < E_COMPONENT::E_COMPONENT_MAX) ? true : false;
    }

    bool IsValidAlgorithm(E_ALGORITHM comp) {
        return (comp >= E_ALGORITHM::E_ALGORITHM_ROTATE && 
                comp < E_ALGORITHM::E_ALGORITHM_MAX) ? true : false;
    }
}