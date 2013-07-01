#ifndef ENTITYCOMPONENT_H
#define ENTITYCOMPONENT_H

#include <GL/glew.h>

// Standard C++ libraries

namespace backlash {
    enum class E_COMPONENT ;

    class EntityComponent {
    public:
        EntityComponent(E_COMPONENT);
        ~EntityComponent();

        virtual void Update() = 0;
        GLuint GetID() const;
        E_COMPONENT GetType() const;

    private:
        const GLuint mID;
        const E_COMPONENT mType;

    };
}

#endif