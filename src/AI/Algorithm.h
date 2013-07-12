#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>

namespace backlash {
    class Algorithm {
    public:
        virtual ~Algorithm(); // Probably create this, just in case.

        virtual void Update() = 0; 

    protected:
        Algorithm();
    };
}

#endif