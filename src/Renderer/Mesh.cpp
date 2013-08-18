// GL Library
#include <GL/glew.h>

// Standard Library
#include <iostream>

// Backlash Library
#include "Mesh.h"

namespace backlash {
        // Mesh stuff
    Mesh::Mesh(int id) : mID(id) {
        mVertexBuffer = INVALID_OGL_VALUE;
        mIndexBuffer = INVALID_OGL_VALUE;
        mNumIndices = 0;
        mMaterialName = "";
        // mName = "";
    }

    Mesh::~Mesh() {
        if (mVertexBuffer != INVALID_OGL_VALUE) {
            glDeleteBuffers(1, &mVertexBuffer);
        }

        if (mIndexBuffer != INVALID_OGL_VALUE) {
            glDeleteBuffers(1, &mIndexBuffer);
        }
    }

    void Mesh::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
        mNumIndices = indices.size();

        glGenBuffers(1, &mVertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        std::cout << "Size of Vector of Vertices: " << sizeof(Vertex) << " * " << vertices.size() << " = " << sizeof(Vertex) * vertices.size() << std::endl;
        glGenBuffers(1, &mIndexBuffer) ;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mNumIndices, &indices[0], GL_STATIC_DRAW);
        std::cout << "Size of Vector of Indices: " << sizeof(unsigned int) << " * " << mNumIndices << " = " << sizeof(unsigned int) * mNumIndices << std::endl;

        std::cout << "Initialized Vertex Buffer: " << mVertexBuffer << std::endl;
        std::cout << "Initialized Index Buffer: " << mIndexBuffer << std::endl;
    }
}