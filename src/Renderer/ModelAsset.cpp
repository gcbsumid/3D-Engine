#include "ModelAsset.h"
#include "util.h"

backlash::ModelAsset::ModelAsset() : 
                         mVBO(0),
                         mVAO(0),
                         mDrawType(GL_TRIANGLES),
                         mDrawStart(0),
                         mDrawCount(0),
                         mShininess(0.2),
                         mSpecularColor(glm::vec3(1.0)),
                         mID(utility::GenerateAssetID()) {}

backlash::ModelAsset::~ModelAsset() {}

