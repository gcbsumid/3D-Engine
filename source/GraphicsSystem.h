#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include <GL/glew.h>

#include "EntityComponent.h"
#include "DrawComponent.h"
#include "CameraComponent.h"

#include <map>
#include <list>

typedef std::map<GLuint,std::shared_ptr<backlash::EntityComponent> > COMPONENT_LIST;
typedef std::map<GLuint,std::shared_ptr<backlash::ModelAsset> > ASSET_LIST;

namespace backlash {
    class GraphicsSystem {
    public:
        static GraphicsSystem& getInstance() {
            static GraphicsSystem instance;
            return instance;
        }

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

        std::list<GLuint> mDrawComponentIDs;
        GLuint mCameraID;

        // Don't Implement copy constructor
        GraphicsSystem(const GraphicsSystem&);
        void operator=(const GraphicsSystem&);
    };
}

#endif