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

    bool DrawComponent::Render() {
        // Do the rendering here
        if (!mShader->IsInUuse()) 
            mShader->Use();

        // TODO: Render the materials for each mesh and then render each mesh. 
        
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

    Program* DrawComponent::GetShader() const {
        return mShader.lock().get();
    }
}