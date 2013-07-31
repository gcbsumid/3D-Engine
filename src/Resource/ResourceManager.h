#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Game/Engine.h" 
#include "../Renderer/Texture.h"
#include "../Renderer/Mesh.h"

#include <memory>
#include <map>
#include <vector>
#include <string>

namespace backlash {
    class Engine;

    class ResourceManager {
        typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
        typedef std::weak_ptr<Engine> EnginePtr;
    public:
        static ResourceManagerPtr GetInstance(EnginePtr parent);

        ~ResourceManager() {}

        void SetTextureSharedPointer(std::map<std::string, Texture*>* textures);
        void SetMeshSharedPointer(std::map<std::string, Mesh*>* meshes);

        void LoadAllFiles();

    private:
        void Clear();
        void LoadAssetFromFile(const string file); 
        void ProcessScene(aiScene*);

        // This is shared with the Graphics manager
        std::shared_ptr<std::map<std::string, Texture*> > mTextures;
        std::shared_ptr<std::map<std::string, Mesh*> > mMeshes;

        // std::vector<Mesh> mLocalMeshes;
        // std::map<std::string, Texture*> mLocalTexture;
        std::vector<std::string> mLocalTexture;

        ResourceManager(EnginePtr parent);
        
        static ResourceManagerPtr mInstance;

        ResourceManager(const ResourceManager&);
        void operator=(const ResourceManager&);
    };
}

#endif