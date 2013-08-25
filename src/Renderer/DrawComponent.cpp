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
        // std::cout << "modelLoc: " << modelLoc << std::endl;
        // model->DisplayModelAttrib();
        // std::cout << "Cup VBO: " << mesh->mVertexBuffer << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, mesh->mVertexBuffer);        
        glBindVertexArray(mesh->mVertexArray);

        // std::cout << "Cup VAO: " << mesh->mVertexArray << std::endl;
        // std::cout << "Index Buffer: " << mesh->mIndexBuffer << std::endl;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mIndexBuffer);
        glDrawElements(GL_TRIANGLES, mesh->mNumIndices, GL_UNSIGNED_INT, 0);

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
        
        model->mBoundingBox = mesh->mBoundingBox;
        AABB box = model->ComputeBoundingBox();

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