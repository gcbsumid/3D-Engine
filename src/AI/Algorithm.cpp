#include "Algorithm.h"

namespace backlash {
    Algorithm::Algorithm(Algorithm::AICompPtr comp) : 
        mChild(NULL),
        mCompParent(comp) 
        {}

    Algorithm::Algorithm(Algorithm::AICompPtr comp, 
                         std::shared_ptr<Algorithm> alg) : 
        mChild(alg),
        mComponent(comp) 
        {}

    Algorithm::~Algorithm() {}
}
