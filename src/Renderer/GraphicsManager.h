#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "../Game/Engine.h"
#include "../Game/Component.h"
#include "DrawComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "ModelAsset.h"
#include "Program.h"
#include "Texture.h"

#include <map>
#include <list>
#include <vector>
#include <memory>

// TODO: Modify the cpp file

typedef std::map<int,std::shared_ptr<backlash::ModelAsset> > ASSET_LIST;

namespace backlash {
    class Engine;

    class GraphicsManager {
        typedef std::shared_ptr<GraphicsManager> GraphicsManagerPtr;
        typedef std::weak_ptr<Engine> EnginePtr;
    public:
        static GraphicsManagerPtr GetInstance(EnginePtr parent);

        ~GraphicsManager() {}

        void AddCameraComponent(std::weak_ptr<CameraComponent>);
        void AddDrawComponent(std::weak_ptr<DrawComponent>);
        void AddLightComponent(std::weak_ptr<LightComponent>);
        void AddTextures(std::vector<Texture>);

        void Render() const ;

        void SetTextureSharedPointer(std::map<std::string, Texture*> textures);
        void SetMeshSharedPointer(std::vector<Mesh> meshes);

    private:
        void RenderInstance(std::shared_ptr<DrawComponent>, 
                            std::shared_ptr<ModelAsset>, 
                            std::shared_ptr<LightComponent>,
                            std::shared_ptr<CameraComponent>) const;

        GraphicsManager(EnginePtr parent);      

        static GraphicsManagerPtr mInstance;

        const EnginePtr mParent;

        std::list<std::weak_ptr<DrawComponent> > mDrawComponents;
        std::vector<std::weak_ptr<LightComponent> > mLightComponents;
        std::weak_ptr<CameraComponent> mCameraComponent;

        std::map<int, std::unique_ptr<Program> > mShaders;

        // this is shared with the resource manager
        std::shared_ptr<std::map<std::string, Texture*> > mTextures;
        std::shared_ptr<std::vector<Mesh> > mMeshes;

        // Don't Implement copy constructor
        GraphicsManager(const GraphicsManager&);
        void operator=(const GraphicsManager&);
    };
}

#endif