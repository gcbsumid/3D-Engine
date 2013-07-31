#ifndef MESH_H
#define MESH_H

namespace backlash {
    struct Vertex {
        glm::vec3 mPosition;    // (x,y,z)
        glm::vec2 mTexCoord;    // (u,v)
        glm::vec3 mNormal;      // (x,y,z)

        Vertex() {};
        Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3 normal) {
            mPosition = pos;
            mTexCoord = tex;
            mNormal = normal;
        }
    };

    struct Mesh {
        Mesh(int);
        ~Mesh();

        // Probably don't need this right now
        void Init(const std::vector<Vertex>* vertices, const std::vector<unsigned int>& indices);
        
        int mID;
        std::string mName;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;

        unsigned int mNumIndices; 
        std::string mMaterialName;        
    };
}

#endif