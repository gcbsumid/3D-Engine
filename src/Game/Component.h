#ifndef COMPONENT_H
#define COMPONENT_H

// Backlash Library
#include "../Util/enum.h"
#include "../Renderer/Program.h"

namespace backlash {
    enum COMPONENT ;

    class Component {
    public:
        Component(COMPONENT);
        ~Component();

        virtual void Update() = 0;
        virtual bool Render(Program*) = 0;
        
        int GetID() const;
        COMPONENT GetType() const;

    private:
        const int mID;
        const COMPONENT mType;

    };
}

#endif