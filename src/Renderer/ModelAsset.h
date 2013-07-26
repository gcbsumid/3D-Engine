#ifndef MODELASSET_H
#define MODELASSET_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <memory>

#include "Program.h"
#include "Texture.h"

namespace backlash {
    struct ModelAsset {
        ModelAsset();
        ~ModelAsset();

        // Material data
        int mShaderID;    // this is now in the mesh entry
        int mTextureID;   // this is now in the mesh entry

        // Mesh data
        GLuint mVBO;                    // now in the mesh data
        GLuint mVAO;                    // now in the mesh data
        // The following are parameters to glDrawArrays
        GLenum mDrawType;
        GLint mDrawStart;
        GLint mDrawCount;

        GLfloat mShininess; 
        glm::vec3 mSpecularColor;
        const GLuint mID;
    };
}

#endif