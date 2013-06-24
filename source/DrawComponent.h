#ifndef DRAWCOMPONENT_H
#define DRAWCOMPONENT_H

#include "EntityComponent.h"
#include "ModelAsset.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace backlash {
    class DrawComponent : public EntityComponent {
    public:
        DrawComponent(GLuint);
        ~DrawComponent();

        void Update();

        void SetTransform(glm::mat4);
        glm::mat4 GetTransform() const;
        
        GLuint GetAssetID() const;

    private:
        GLuint mAssetID;
        glm::mat4 mTransform;
    } ;
}

#endif 