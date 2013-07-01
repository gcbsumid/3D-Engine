#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include <GL/glew.h>

#include "Engine.h"
#include "EntityComponent.h"
#include "DrawComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "ModelAsset.h"

#include <map>
#include <list>
#include <vector>
#include <memory>

typedef std::map<GLuint,std::shared_ptr<backlash::EntityComponent> > COMPONENT_LIST;
typedef std::map<GLuint,std::shared_ptr<backlash::ModelAsset> > ASSET_LIST;

namespace backlash {
    class Engine;

    class GraphicsSystem {
        typedef std::shared_ptr<GraphicsSystem> GraphicsSystem_ptr;
        typedef std::shared_ptr<Engine> Engine_ptr;
    public:
        static GraphicsSystem_ptr GetInstance(Engine_ptr parent);

        ~GraphicsSystem() {}

        void AddCameraComponent(GLuint);
        void AddDrawComponent(GLuint);
        void AddLightComponent(GLuint);
        void Render() const ;

    private:
        void RenderInstance(std::shared_ptr<DrawComponent>, 
                            std::shared_ptr<ModelAsset>, 
                            std::shared_ptr<LightComponent>,
                            std::shared_ptr<CameraComponent>) const;

        GraphicsSystem(Engine_ptr parent);      

        static GraphicsSystem_ptr mInstance;

        const Engine_ptr mParent;

        std::list<GLuint> mDrawComponentIDs;
        std::vector<GLuint> mLightComponentIDs;
        GLuint mCameraComponentID;

        // Don't Implement copy constructor
        GraphicsSystem(const GraphicsSystem&);
        void operator=(const GraphicsSystem&);
    };
}

#endif