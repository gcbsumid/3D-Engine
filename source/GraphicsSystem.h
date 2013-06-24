#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include <GL/glew.h>

#include "DrawComponent.h"

#include <map>
#include <list>

namespace backlash {
    class GraphicsSystem {
    public:
        static GraphicsSystem& getInstance()
        {
            static GraphicsSystem instance;
            return instance;
        }

        ~GraphicsSystem() {}

        void AddCameraComponent(GLuint);
        void AddDrawComponent(GLuint);
        void Render(const std::map<GLuint,DrawComponent>&) const;

    private:
        void RenderInstance(const DrawComponent&, const ModelAsset&, const CameraComponent&) const;

        GraphicsSystem();      

        std::list<GLuint> mDrawComponentIDs;
        GLuint mCameraID;

        // Don't Implement copy constructor
        GraphicsSystem(GraphicsSystem const&);
        void operator=(GraphicsSystem const&);
    };
}

#endif