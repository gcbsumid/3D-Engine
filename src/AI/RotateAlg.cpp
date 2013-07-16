#include "RotateAlg.h"
#include "AIComponent.h"

namespace backlash  {
    RotateAlg::RotateAlg(Algorithm::AICompPtr comp) : 
        Algorithm(comp) {}

    RotateAlg::RotateAlg(Algorithm::AICompPtr comp, 
                         shared_ptr<Algorithm> child) : 
        Algorithm(comp, child) {}

    RotateAlg::~RotateAlg() {}

    void RotateAlg::Run() {
        // Mess with the parent's stuff
        // ex. mCompParent->mAttrib
    }  
}