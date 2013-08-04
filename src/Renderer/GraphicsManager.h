#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

// Standard Library
#include <map>
#include <vector>
#include <memory>

// Backlash Library
#include "../Game/Engine.h"
#include "../Game/Component.h"
#include "DrawComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "Program.h"
#include "Shader.h"
#include "Texture.h"

namespace backlash {
    class Engine;

    class GraphicsManager {
    public:
        static GraphicsManager* GetInstance();

        ~GraphicsManager() {}

        void Render() const ;

        void LoadShaders();

        void AddCameraComponent(std::shared_ptr<CameraComponent>);
        void AddDrawComponent(std::shared_ptr<DrawComponent>);
        void AddLightComponent(std::shared_ptr<LightComponent>);

        void SetTextureSharedPointer(std::shared_ptr<std::map<std::string, Texture*>>& textures);
        void SetMeshSharedPointer(std::shared_ptr<std::map<std::string, Mesh*>>& meshes);

        static void AttachShaderToDrawComponent(DrawComponent*, int);
        static void AttachMeshToDrawComponent(DrawComponent*, std::string);

    private:
        GraphicsManager();      

        static GraphicsManager* mInstance;

        std::vector<std::weak_ptr<DrawComponent> > mDrawComponents;
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