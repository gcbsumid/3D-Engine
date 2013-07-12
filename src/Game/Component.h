#ifndef COMPONENT_H
#define COMPONENT_H

#include <GL/glew.h>

// Standard C++ libraries

namespace backlash {
    enum class E_COMPONENT ;

    class Component {
    public:
        Component(E_COMPONENT);
        ~Component();

        virtual void Update() = 0;
        GLuint GetID() const;
        E_COMPONENT GetType() const;

    private:
        const GLuint mID;
        const E_COMPONENT mType;

    };
}

#endif