#ifndef ENTITYCOMPONENT_H
#define ENTITYCOMPONENT_H

#include <GL/glew.h>

// Standard C++ libraries

namespace backlash {
    class EntityComponent {
    public:
        EntityComponent();
        ~EntityComponent();

        virtual void Update() = 0;
        GLuint GetID() ;

    private:
        const GLuint mID;
    };
}

#endif