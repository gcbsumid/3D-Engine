#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include <GL/glew.h>

#include "EntityComponent.h"
#include "DrawComponent.h"
#include "CameraComponent.h"

#include <map>
#include <list>
#include <memory>

typedef std::map<GLuint,std::shared_ptr<backlash::EntityComponent> > COMPONENT_LIST;
typedef std::map<GLuint,std::shared_ptr<backlash::ModelAsset> > ASSET_LIST;

namespace backlash {
    class GraphicsSystem {
    public:
        static std::shared_ptr<GraphicsSystem> GetInstance();

        ~GraphicsSystem() {}

        void AddCameraComponent(GLuint);
        void AddDrawComponent(GLuint);
        void Render(COMPONENT_LIST& components, 
                    ASSET_LIST& assets) const ;

    private:
        void RenderInstance(std::shared_ptr<DrawComponent>, 
                            std::shared_ptr<ModelAsset>, 
                            std::shared_ptr<CameraComponent>) const;

        GraphicsSystem();      

        static std::shared_ptr<GraphicsSystem> mInstance;

        std::list<GLuint> mDrawComponentIDs;
        GLuint mCameraComponentID;

        // Don't Implement copy constructor
        GraphicsSystem(const GraphicsSystem&);
        void operator=(const GraphicsSystem&);
    };
}

#endif