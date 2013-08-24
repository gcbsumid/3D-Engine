#ifndef MESH_H
#define MESH_H

// GLM Library
#include <glm/glm.hpp>

// Standard Library
#include <string>
#include <vector>

// Backlash Library
#include "../Util/defines.h"
#include "AABB.h"

namespace backlash {
    struct Vertex {
        float x, y, z;    // (x,y,z)
        // glm::vec2 mTexCoord;    // (u,v)
        // glm::vec3 mNormal;      // (x,y,z)

        Vertex() {};
        Vertex(const glm::vec3& pos) { //, const glm::vec2& tex, const glm::vec3 normal) {
            x = pos.x;
            y = pos.y;
            z = pos.z;
            // mPosition = pos;
            // mTexCoord = tex;
            // mNormal = normal;
        }
    };

    struct Mesh {
        Mesh(int);
        ~Mesh();

        void Init(const std::vector<Vertex>& vertices, 
                  const std::vector<unsigned int>& indices,
                  const AABB& box);
        
        int mID;
        // std::string mName;
        GLuint mVertexBuffer;
        GLuint mVertexArrayObject;
        GLuint mIndexBuffer;

        AABB mBoundingBox;

        unsigned int mNumIndices; 
        std::string mMaterialName;        
    };
}

#endif