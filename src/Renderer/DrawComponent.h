#ifndef DRAWCOMPONENT_H
#define DRAWCOMPONENT_H

// GLM Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Standard Library
#include <memory>
#include <string>

#include "../Game/Component.h"
#include "../Game/ModelAttrib.h"
#include "../Game/ComponentFactory.h"
#include "../Util/enum.h"
#include "Mesh.h"
#include "Program.h"

namespace backlash {
    enum COMPONENT;

    class DrawComponent : public Component {
    friend class ComponentFactoryInitializer;
    friend class Factory;

    DrawComponent();
    ~DrawComponent();

    class Factory : public ComponentFactory {
    friend class ComponentFactoryInitializer;
    public:
        Component* Create() {
            return new DrawComponent;
        }
    };

    public:
        virtual void Update();
        virtual bool Render(Program*);

        void SetShader(Program* program);
        void SetMesh(std::shared_ptr<Mesh> mesh);
        void SetModelAttrib(std::shared_ptr<ModelAttrib> model);
        std::string GetMaterialName() const;
        Program* GetShader() const;
        std::shared_ptr<ModelAttrib> GetModelAttrib();

    private:
        std::weak_ptr<Mesh> mMesh;
        Program* mShader;

        std::weak_ptr<ModelAttrib> mModel;
    } ;
}

#endif 