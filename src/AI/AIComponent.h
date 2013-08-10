#ifndef AICOMPONENT_H
#define AICOMPONENT_H

// Standard Library
#include <memory>
#include <map>

// Backlash Library
#include "Algorithm.h"
#include "../Game/Component.h"
#include "../Game/ModelAttrib.h"
#include "../Game/ComponentFactory.h"
#include "../Util/enum.h"
#include "../Renderer/Program.h"

 // TODO: will pass in the status to determine which algorithm will be used.

namespace backlash {
    enum E_ALGORITHM;

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
        virtual void Update();
        virtual bool Render(Program*); 

        void SetModelMatrix(std::shared_ptr<ModelAttrib> model);
        void GenerateAlgorithm(E_ALGORITHM);
        void ClearAlgorithms();
    private: 
        std::map<E_ALGORITHM,std::unique_ptr<Algorithm>> mAlgorithms; 
        std::weak_ptr<ModelAttrib> mModel; 
    };
}

#endif