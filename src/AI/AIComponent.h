#ifndef AICOMPONENT_H
#define AICOMPONENT_H

// Standard Library
#include <memory>
#include <vector>

// Backlash Library
#include "Algorithm.h"
#include "../Game/Component.h"
#include "../Game/ModelAttrib.h"
#include "../Game/ComponentFactory.h"
#include "../Util/enum.h"
#include "../Renderer/Program.h"

 // TODO: will pass in the status to determine which algorithm will be used.

namespace backlash {
    enum ALGORITHM;
    class Algorithm;

    class AIComponent : public Component {
        // Algorithms
        friend class RotateAlg;
        friend class TranslateAlg;

        // Component Factory
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
        void Action(double);

        void SetModelAttrib(std::shared_ptr<ModelAttrib> model);
        void GenerateAlgorithm(ALGORITHM);
        void ClearAlgorithms();
    private: 
        // std::map<int, Algorithm*> mLocalAlgos;
        std::vector<std::unique_ptr<Algorithm>> mAlgorithms; 
        std::weak_ptr<ModelAttrib> mModel; 
    };
}

#endif