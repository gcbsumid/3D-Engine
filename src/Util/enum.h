#ifndef ENUM_H
#define ENUM_H

// Standard Library
#include <type_traits>

namespace backlash {
    // template <typename Enumeration> 
    // auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
    //     return static_cast<typename std::underlying_type<Enumeration>::type>(value);
    // }

    enum COMPONENT {  
        COMPONENT_DRAW = 0,
        COMPONENT_CAMERA,
        COMPONENT_LIGHT,
        COMPONENT_AI,

        COMPONENT_MAX
    } ;

    enum ALGORITHM {
        ALGORITHM_ROTATE = 0,
        ALGORITHM_TRANSLATE,

        ALGORITHM_MAX
    };

    enum LIGHT {
        LIGHT_DIRECTIONAL = 0,
        LIGHT_POINT, 
        LIGHT_SPOT,

        LIGHT_MAX
    };

    extern bool IsValidComponent(COMPONENT);
    extern bool IsValidAlgorithm(ALGORITHM);
    extern bool IsValidLight(LIGHT);
}

#endif