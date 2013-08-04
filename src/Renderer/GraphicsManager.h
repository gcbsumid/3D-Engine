#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "../Game/Engine.h"
#include "../Game/Component.h"
#include "DrawComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "Program.h"
#include "Shader.h"
#include "Texture.h"

#include <map>
#include <list>
#include <vector>
#include <memory>

namespace backlash {
    class Engine;

    class GraphicsManager {
        typedef std::shared_ptr<GraphicsManager> GraphicsManagerPtr;
        typedef std::weak_ptr<Engine> EnginePtr;
    public:
        static GraphicsManagerPtr GetInstance(Engine* parent);

        ~GraphicsManager() {}

        void LoadShaders();

        void AddCameraComponent(CameraComponent*);
        void AddDrawComponent(DrawComponent*);
        void AddLightComponent(LightComponent*);
        void AddTextures(std::vector<Texture>);

        void AttachShaderToDrawComponent(DrawComponent*, int);
        void AttachMeshToDrawComponent(DrawComponent*, std::string);

        void Render() const ;

        void SetTextureSharedPointer(std::map<std::string, Texture*>* textures);
        void SetMeshSharedPointer(std::map<std::string, Mesh*>* meshes);

    private:
        // void RenderInstance(std::shared_ptr<DrawComponent>, 
        //                     std::shared_ptr<ModelAsset>, 
        //                     std::shared_ptr<LightComponent>,
        //                     std::shared_ptr<CameraComponent>) const;

        GraphicsManager(EnginePtr parent);      

        static GraphicsManagerPtr mInstance;

        const EnginePtr mParent;

        std::list<std::weak_ptr<DrawComponent> > mDrawComponents;
        std::vector<std::weak_ptr<LightComponent> > mLightComponents;
        std::weak_ptr<CameraComponent> mCameraComponent;

        // this is shared with the resource manager
        std::shared_ptr<std::map<std::string, Texture*> > mTextures;
        std::shared_ptr<std::map<std::string, Mesh*> > mMeshes;

        Program* mActiveShader;
        std::vector<Program*> mShaders;

        // Don't Implement copy constructor
        GraphicsManager(const GraphicsManager&);
        void operator=(const GraphicsManager&);
    };
}

#endif