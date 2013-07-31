#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include <GL/glew.h>

#include "Algorithm.h"
#include "../Game/Component.h"
#include "../Game/ModelAttrib.h"
#include "../Game/ComponentFactory.h"
#include "../Util/enum.h"
#include "../Renderer/Program.h"

#include <vector> 
#include <memory>

 // TODO: will pass in the status to determine which algorithm will be used.

namespace backlash {
    enum class E_ALGORITHM;

    class AIComponent : public Component {
        friend class Algorithm;
        friend class ComponentFactoryInitializer;
        friend class Factory;

        AIComponent();
        ~AIComponent();

        class Factory : public ComponentFactory {
        friend class ComponentFactoryInitializer;
        public:
            Component* Create() {
                return new AIComponent;
            }
        };

    public:
        virtual void Init();
        virtual void Update();
        virtual bool Render(Program*); 

        void SetModelMatrix(std::weak_ptr<ModelAttrib> model);
        void GenerateAlgorithm(E_ALGORITHM);
        void ClearAlgorithm();
    private: 
        Algorithm* mAlgorithm; 
        std::weak_ptr<ModelAttrib> mModel bv; 
    };
}

#endif