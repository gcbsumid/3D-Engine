// GL Library 
#include <GL/glew.h>

// Standard Library
#include <cassert>
#include <iostream>

// Backlash Library
#include "DrawComponent.h"
#include "../Util/defines.h"

namespace backlash {
    DrawComponent::DrawComponent() : 
        Component(E_COMPONENT_DRAW) {}

    DrawComponent::~DrawComponent() {}

    void DrawComponent::Update() {
        // Do something?
    }

    bool DrawComponent::Render(Program* shader) {
        assert(mMesh.use_count());
        assert(mModel.use_count());

        auto mesh = mMesh.lock();
        auto model = mModel.lock();

        GLint modelLoc = shader->Uniform("model");

        // std::cout << "modelLoc: " << modelLoc << std::endl;

        glm::mat4 matrix = model->mTransform;
        std::cout << "Model Transform: " << std::endl;
        std::cout << "\t{ " << matrix[0][0] << " ,\t" << matrix[0][1] << " ,\t" << matrix[0][2] << " ,\t" <<matrix[0][3] << "}" << std::endl;
        std::cout << "\t{ " << matrix[1][0] << " ,\t" << matrix[1][1] << " ,\t" << matrix[1][2] << " ,\t" <<matrix[1][3] << "}" << std::endl;
        std::cout << "\t{ " << matrix[2][0] << " ,\t" << matrix[2][1] << " ,\t" << matrix[2][2] << " ,\t" <<matrix[2][3] << "}" << std::endl;
        std::cout << "\t{ " << matrix[3][0] << " ,\t" << matrix[3][1] << " ,\t" << matrix[3][2] << " ,\t" <<matrix[3][3] << "}" << std::endl;

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model->mTransform));

        std::cout << "Vertext Buffer: " << mesh->mVertexBuffer << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, mesh->mVertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)sizeof(glm::vec3));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

        std::cout << "Index Buffer: " << mesh->mIndexBuffer << std::endl;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mIndexBuffer);
        glDrawElements(GL_TRIANGLES, mesh->mNumIndices, GL_UNSIGNED_INT, 0);

        return true;
    }

    void DrawComponent::SetShader(Program* program) {
        assert(program);
        mShader = program;
    }

    void DrawComponent::SetMesh(std::shared_ptr<Mesh> mesh) {
        assert(mesh.use_count());
        mMesh = mesh;
    }

    void DrawComponent::SetModelAttrib(std::shared_ptr<ModelAttrib> model) {
        assert(model.use_count());
        mModel = model;
    }

    std::string DrawComponent::GetMaterialName() const {
        assert(mMesh.use_count());
        auto mesh = mMesh.lock();
        return mesh->mMaterialName;
    }

    Program* DrawComponent::GetShader() const {
        return mShader;
    }
}