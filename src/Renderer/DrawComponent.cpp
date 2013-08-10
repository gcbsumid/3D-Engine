#include "DrawComponent.h"
#include <GL/glew.h>
#include <cassert>

namespace backlash {
    DrawComponent::DrawComponent() : 
        Component(E_COMPONENT_DRAW) {}

    DrawComponent::~DrawComponent() {}

void DrawComponent::Update() {
        // Do something?
    }

    bool DrawComponent::Render(Program* shader) {
        GLuint shaderLoc = shader->Object();
        GLuint modelLoc = glGetUniformLocation(shader, "model");
        assert(CHECKINVALID(modelLoc));

        glUniformMatrix4fv(modelLoc, 1, transpose, glm::value_ptr(modelLoc->mTransform));

        glBindBuffer(GL_ARRAY_BUFFER, mMesh->mVertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mMesh->mIndexBuffer);
        glDrawElements(GL_TRIANGLES, mMesh->mNumIndices, GL_UNSIGNED_INT, 0);

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
        return mMesh->mMaterialName;
    }

    Program* DrawComponent::GetShader() const {
        return mShader.lock().get();
    }
}