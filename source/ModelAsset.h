#ifndef MODELASSET_H
#define MODELASSET_H

#include <GL/glew.h>
#include <memory>

#include "Program.h"
#include "Texture.h"

namespace backlash {
    struct ModelAsset {
        ModelAsset();
        ~ModelAsset();

        // Material data
        std::unique_ptr<backlash::Program> mShaders;    // the program
        std::unique_ptr<backlash::Texture> mTextures;   // textures

        // Mesh data
        GLuint mVBO;                    // vertex buffer object id; 
        GLuint mVAO;                    // vertex array object id
        // The following are parameters to glDrawArrays
        GLenum mDrawType;
        GLint mDrawStart;
        GLint mDrawCount;

        const GLuint mID;
    };
}

#endif