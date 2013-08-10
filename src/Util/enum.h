#ifndef ENUM_H
#define ENUM_H

// Standard Library
#include <type_traits>

namespace backlash {
    // template <typename Enumeration> 
    // auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
    //     return static_cast<typename std::underlying_type<Enumeration>::type>(value);
    // }

    enum E_COMPONENT {  
        E_COMPONENT_DRAW = 0,
        E_COMPONENT_CAMERA,
        E_COMPONENT_LIGHT,
        E_COMPONENT_AI,

        E_COMPONENT_MAX
    } ;

    enum E_ALGORITHM {
        E_ALGORITHM_ROTATE = 0,
        E_ALGORITHM_TRANSLATE,

        E_ALGORITHM_MAX
    };

    extern bool IsValidComponent(E_COMPONENT comp) {
        return (comp >= E_COMPONENT::E_COMPONENT_DRAW && 
                comp < E_COMPONENT::E_COMPONENT_MAX) ? true : false;
    }

    extern bool IsValidAlgorithm(E_ALGORITHM comp) {
        return (comp >= E_ALGORITHM::E_ALGORITHM_ROTATE && 
                comp < E_ALGORITHM::E_ALGORITHM_MAX) ? true : false;
    }
}

#endif