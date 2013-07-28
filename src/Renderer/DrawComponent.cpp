#include "DrawComponent.h"
#include <GL/glew.h>
#include <cassert>

namespace backlash {
    DrawComponent::DrawComponent() : 
        Component(E_COMPONENT::E_COMPONENT_DRAW) {}

    DrawComponent::~DrawComponent() {}

    void DrawComponent::Init() {
        // Do something?
    }

void DrawComponent::Update() {
        // Do something?
    }

    bool DrawComponent::Render(Program* shader) {

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
        mShader = std::weak_ptr<Program>(program);
    }

    void DrawComponent::SetMesh(Mesh* mesh) {
        assert(mesh);
        mMesh = std::weak_ptr<Mesh>(mesh);
    }

    void DrawComponent::SetModelAttrib(ModelAttrib* model) {
        assert(model);
        mModel = std::weak_ptr<ModelAttrib>(model);
    }

    std::string DrawComponent::GetMaterialName() const {
        return mMesh->mMaterialName;
    }

    Program* DrawComponent::GetShader() const {
        return mShader.lock().get();
    }
}