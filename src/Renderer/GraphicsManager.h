#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

// Standard Library
#include <map>
#include <vector>
#include <memory>

// Backlash Library
#include "../Game/Component.h"
#include "DrawComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "Program.h"
#include "Shader.h"
#include "Texture.h"

namespace backlash {
    class GraphicsManager {
    public:
        static GraphicsManager* GetInstance();

        ~GraphicsManager() {}

        void Render() ;

        void LoadShaders();

        void AddCameraComponent(std::shared_ptr<CameraComponent>);
        void AddDrawComponent(std::shared_ptr<DrawComponent>);
        void AddLightComponent(std::shared_ptr<LightComponent>);

        void SetTextureSharedPointer(std::shared_ptr<std::map<std::string, Texture*>>& textures);
        void SetMeshSharedPointer(std::shared_ptr<std::map<int, std::shared_ptr<Mesh>>>& meshes);

        void AttachShaderToDrawComponent(DrawComponent*, int);
        void AttachMeshToDrawComponent(DrawComponent*, int);

        // TEMP
        void LoadCube();

    private:
        GraphicsManager();      

        static GraphicsManager* mInstance;

        std::vector<std::weak_ptr<DrawComponent>> mDrawComponents;
        std::vector<std::weak_ptr<LightComponent>> mLightComponents;
        std::weak_ptr<CameraComponent> mCameraComponent;

        // this is shared with the resource manager
        std::shared_ptr<std::map<std::string, Texture*>> mTextures;
        std::shared_ptr<std::map<int, std::shared_ptr<Mesh>>> mMeshes;

        Program* mActiveShader;
        std::vector<Program*> mShaders;

        // Don't Implement copy constructor
        GraphicsManager(const GraphicsManager&);
        void operator=(const GraphicsManager&);

        // TEMP
        GLuint gVAO;
        GLuint gVBO;
        GLenum drawType;
        GLint drawStart;
        GLint drawCount;
        Texture* crateTexture;
        glm::mat4 transform;
    };
}

#endif