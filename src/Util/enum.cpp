#include "enum.h"

namespace backlash {
    bool IsValidComponent(COMPONENT comp) {
        return (comp >= COMPONENT::COMPONENT_DRAW && 
                comp < COMPONENT::COMPONENT_MAX) ? true : false;
    }

    bool IsValidAlgorithm(ALGORITHM algo) {
        return (algo >= ALGORITHM::ALGORITHM_ROTATE && 
                algo < ALGORITHM::ALGORITHM_MAX) ? true : false;
    }

    bool IsValidLight(LIGHT light) {
        return (light >= LIGHT::LIGHT_DIRECTIONAL && 
                light < LIGHT::LIGHT_MAX) ? true : false;
    }
}