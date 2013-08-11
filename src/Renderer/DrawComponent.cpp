// GL Library 
#include <GL/glew.h>

// Standard Library
#include <cassert>

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

        GLuint shaderLoc = shader->Object();
        GLuint modelLoc = glGetUniformLocation(shaderLoc, "model");
        assert(CHECKINVALID(modelLoc));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model->mTransform));

        glBindBuffer(GL_ARRAY_BUFFER, mesh->mVertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

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