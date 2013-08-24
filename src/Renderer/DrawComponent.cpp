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

        shader->SetUniform("model", model->mTransform);
        // GLint modelLoc = shader->Uniform("model");
        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model->mTransform));

        // std::cout << "modelLoc: " << modelLoc << std::endl;

        model->DisplayModelAttrib();


        std::cout << "Cup VBO: " << mesh->mVertexBuffer << std::endl;
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->mVertexBuffer);
        
        glBindVertexArray(mesh->mVertexArrayObject);

        std::cout << "Cup VAO: " << mesh->mVertexArrayObject << std::endl;
        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)sizeof(glm::vec3));
        // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

        std::cout << "Index Buffer: " << mesh->mIndexBuffer << std::endl;
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mIndexBuffer);
        glDrawArrays(GL_TRIANGLES, 0, mesh->mNumIndices);
        // glDrawElements(GL_TRIANGLES, mesh->mNumIndices, GL_UNSIGNED_INT, 0);

        return true;
    }

    std::shared_ptr<ModelAttrib> DrawComponent::GetModelAttrib() {
        return mModel.lock();
    }

    void DrawComponent::SetShader(Program* program) {
        assert(program);
        mShader = program;
    }

    void DrawComponent::SetMesh(std::shared_ptr<Mesh> mesh) {
        assert(mesh.use_count());
        assert(mModel.use_count());
        auto model = mModel.lock();
        
        std::cout << "Mesh Bounding Box: " << std::endl;
        glm::vec3 mesh_min = mesh->mBoundingBox.mMin;
        glm::vec3 mesh_max = mesh->mBoundingBox.mMax;
        std::cout << "\tmin: (" << mesh_min.x << ", "  << mesh_min.y << ", " << mesh_min.z << ")" << std::endl;
        std::cout << "\tmax: (" << mesh_max.x << ", "  << mesh_max.y << ", " << mesh_max.z << ")" << std::endl;

        model->mBoundingBox = mesh->mBoundingBox;
        AABB box = model->ComputeBoundingBox();
        std::cout << "Model Bounding Box: " << std::endl;
        glm::vec3 min = box.mMin;
        glm::vec3 max = box.mMax;
        std::cout << "\tmin: (" << min.x << ", "  << min.y << ", " << min.z << ")" << std::endl;
        std::cout << "\tmax: (" << max.x << ", "  << max.y << ", " << max.z << ")" << std::endl;

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