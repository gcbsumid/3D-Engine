#ifndef DRAWCOMPONENT_H
#define DRAWCOMPONENT_H

#include "../Renderer/ModelAsset.h"
#include "../Game/Component.h"
#include "../Game/ModelAttrib.h"
#include "../Game/ComponentFactory.h"
#include "../Util/enum.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

// TODO: Render each draw component

namespace backlash {
    enum class E_COMPONENT;

    class DrawComponent : public Component {
    friend class ComponentFactoryInitializer;
    friend class Factory;

    Drawcomponent();
    ~DrawComponent();

    class Factory : public ComponentFactory {
    friend class ComponentFactoryInitializer;
    public:
        Component* Create() {
            return new DrawComponent;
        }
    };

    public:
        virtual void Init();
        virtual void Update();
        virtual bool Render();

        void SetAsset(int id);
        void SetModelAttrib(std::weak_ptr<ModelAttrib> model);

        int GetAssetID() const;

    private:
        int mAssetID;
        std::weak_ptr<ModelAttrib> mModel;
    } ;
}

#endif 