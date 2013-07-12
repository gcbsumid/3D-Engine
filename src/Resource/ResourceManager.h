#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Engine.h" 
#include "ModelAsset.h"

#include <memory>

namespace backlash {
    class Engine;

    class ResourceManager {
        typedef std::shared_ptr<ResourceManager> ResourceManager_ptr;
        typedef std::shared_ptr<Engine> Engine_ptr;
        typedef std::shared_ptr<ModelAsset> Asset_ptr;
    public:
        static ResourceManager_ptr GetInstance(Engine_ptr parent);

        ~ResourceManager() {}

        Asset_ptr LoadAssetFromFile(const char* file); 
        Asset_ptr ProcessScene(aiScene*);

    private:
        ResourceManager(Engine_ptr parent);
        
        static ResourceManager_ptr mInstance;

        ResourceManager(const ResourceManager&);
        void operator=(const ResourceManager&);
    };
}

#endif