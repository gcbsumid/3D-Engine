#ifndef COMPONENT_H
#define COMPONENT_H

// Backlash Library
#include "../Util/enum.h"
#include "../Renderer/Program.h"

namespace backlash {
    enum class E_COMPONENT ;

    class Component {
    public:
        Component(E_COMPONENT);
        ~Component();

        virtual void Update() = 0;
        virtual bool Render(Program*) = 0;
        
        int GetID() const;
        E_COMPONENT GetType() const;

    private:
        const int mID;
        const E_COMPONENT mType;

    };
}

#endif