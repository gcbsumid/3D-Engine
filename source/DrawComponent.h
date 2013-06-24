#ifndef DRAWCOMPONENT_H
#define DRAWCOMPONENT_H

#include "EntityComponent.h"
#include "ModelAsset.h"
#include <GL/glew.h>

namespace backlash {
    class DrawComponent : public EntityComponent {
    public:
        DrawComponent(GLuint);
        ~DrawComponent();

        void Update();
        GLuint GetAssetID();

    private:
        GLuint mAssetID;
    } ;
}

#endif 