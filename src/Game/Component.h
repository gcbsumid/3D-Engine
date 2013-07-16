#ifndef COMPONENT_H
#define COMPONENT_H

#include <enum.h>

// Standard C++ libraries

namespace backlash {
    enum class E_COMPONENT ;

    class Component {
    public:
        Component(E_COMPONENT);
        ~Component();

        virtual void init() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        
        int GetID() const;
        E_COMPONENT GetType() const;

    private:
        const int mID;
        const E_COMPONENT mType;

    };
}

#endif