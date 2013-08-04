#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

// Assimp Library
#include <assimp/scene.h>

// Standard Library
#include <memory>
#include <map>
#include <vector>
#include <string>

// Backlash Library
#include "../Game/Engine.h" 
#include "../Renderer/Texture.h"
#include "../Renderer/Mesh.h"

namespace backlash {
    class ResourceManager {
    public:
        static ResourceManager* GetInstance();

        ~ResourceManager() {}

        void SetTextureSharedPointer(std::shared_ptr<std::map<std::string, Texture*>>& textures);
        void SetMeshSharedPointer(std::shared_ptr<std::map<std::string, Mesh*>>& meshes);

        void LoadAllFiles();

    private:
        ResourceManager();

        void Clear();
        void InitMaterials(Assimp::aiScene*, const std::string&);
        void InitMesh(Assimp::aiMesh*);
        void SetMaterialData(Assimp::aiMaterial*, Texture*);
        void LoadAssetFromFile(const string file); 
        void ProcessScene(Assimp::aiScene*);

        // This is shared with the Graphics manager
        std::shared_ptr<std::map<std::string, Texture*>> mTextures;
        std::shared_ptr<std::map<std::string, Mesh*>> mMeshes;
        std::vector<std::string> mLocalTexture;
        
        static ResourceManager* mInstance;

        // Things not to implement
        ResourceManager(const ResourceManager&);
        void operator=(const ResourceManager&);
    };
}

#endif