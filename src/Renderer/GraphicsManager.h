#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <GL/glew.h>

#include "Engine.h"
#include "Component.h"
#include "DrawComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "ModelAsset.h"

#include <map>
#include <list>
#include <vector>
#include <memory>

typedef std::map<GLuint,std::shared_ptr<backlash::Component> > COMPONENT_LIST;
typedef std::map<GLuint,std::shared_ptr<backlash::ModelAsset> > ASSET_LIST;

namespace backlash {
    class Engine;

    class GraphicsManager {
        typedef std::shared_ptr<GraphicsManager> GraphicsManager_ptr;
        typedef std::shared_ptr<Engine> Engine_ptr;
    public:
        static GraphicsManager_ptr GetInstance(Engine_ptr parent);

        ~GraphicsManager() {}

        void AddCameraComponent(GLuint);
        void AddDrawComponent(GLuint);
        void AddLightComponent(GLuint);
        void Render() const ;

    private:
        void RenderInstance(std::shared_ptr<DrawComponent>, 
                            std::shared_ptr<ModelAsset>, 
                            std::shared_ptr<LightComponent>,
                            std::shared_ptr<CameraComponent>) const;

        GraphicsManager(Engine_ptr parent);      

        static GraphicsManager_ptr mInstance;

        const Engine_ptr mParent;

        std::list<GLuint> mDrawComponentIDs;
        std::vector<GLuint> mLightComponentIDs;
        GLuint mCameraComponentID;

        // Don't Implement copy constructor
        GraphicsManager(const GraphicsManager&);
        void operator=(const GraphicsManager&);
    };
}

#endif