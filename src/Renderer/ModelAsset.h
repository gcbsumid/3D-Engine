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
        std::weak_ptr<Mesh> mMesh;
        
        const GLuint mID;
    };
}

#endif