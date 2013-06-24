#include "DrawComponent.h"

backlash::DrawComponent::DrawComponent(GLuint id) : backlash::EntityComponent(), mAssetID(id) {}

backlash::DrawComponent::~DrawComponent() {}

void backlash::DrawComponent::Update() {
    // Do something?
}

GLuint backlash::DrawComponent::GetAssetID() {
    return mAssetID;
}