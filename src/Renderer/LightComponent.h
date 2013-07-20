#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

#include "../Game/Component.h"
#include "../Game/ComponentFactory.h"
#include "../Util/enum.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO: The Do the rendering stuff for each light

namespace backlash {
    class LightComponent : public Component {
    friend class ComponentFactoryInitializer;
    friend class Factory;

    LightComponent();
    ~LightComponent();

    class Factory : public ComponentFactory {
    friend class ComponentFactoryInitializer;
    public: 
        Component* Create() {
            return new LightComponent;
        }
    };

    public:
        virtual void init();
        virtual void Update();
        virtual bool Render();

        void SetPosition(glm::vec3);
        glm::vec3 GetPosition() const;

        void SetIntensity(glm::vec3);
        glm::vec3 GetIntensity() const;

        void SetAttenuation(GLfloat);
        GLfloat GetAttenuation() const;

        void SetAmbientCoefficient(GLfloat);
        GLfloat GetAmbientCoefficient() const;
    private:
        glm::vec3 mPosition;
        glm::vec3 mIntensity;
        GLfloat mAttenuation; 
        GLfloat mAmbientCoefficient;
    };
}

#endif