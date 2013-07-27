#ifndef DRAWCOMPONENT_H
#define DRAWCOMPONENT_H

#include "../Game/Component.h"
#include "../Game/ModelAttrib.h"
#include "../Game/ComponentFactory.h"
#include "../Util/enum.h"
#include "Mesh.h"
#include "Program.h"
#include "ModelAsset.h"

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
        virtual bool Render(Program*);

        void SetShader(Program* program);
        void SetMesh(Mesh* mesh);
        void SetModelAttrib(ModelAttrib* model);
        std::string GetMaterialName() const;
        Program* GetShader() const;

    private:
        std::weak_ptr<Mesh> mMesh;
        std::weak_ptr<Program> mShader;

        std::weak_ptr<ModelAttrib> mModel;
    } ;
}

#endif 