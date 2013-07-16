#ifndef ENUM_H
#define ENUM_H

namespace backlash {
    enum class E_COMPONENT {  
        E_COMPONENT_DRAW,
        E_COMPONENT_CAMERA,
        E_COMPONENT_LIGHT,
        E_COMPONENT_AI,

        E_COMPONENT_MAX
    } ;

    enum class E_ALGORITHM {
        E_ALGORITHM_ROTATE,
        E_ALGORITHM_TRANSLATE,

        E_ALGORITHM_MAX
    };
}

#endif