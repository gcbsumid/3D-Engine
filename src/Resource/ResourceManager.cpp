#include "ResourceManager.h"

#include <cassert>
#include <iostream>

// Global static pointer used to ensure my singleton
std::shared_ptr<backlash::GraphicsManager> backlash::GraphicsManager::mInstance;

namespace backlash {
    ResourceManager::ResourceManager_ptr ResourceManager::GetInstance( 
        ResourceManager::Engine_ptr parent) {
        if (mInstance.get() == 0) {
            mInstance = std::shared_ptr<ResourceManager>(new ResourceManager(parent));
        }
        return mInstance;
    }

    ResourceManager::ResourceManager(ResourceManager::Engine_ptr parent) : 
        mParent(parent) {}

    ResourceManager::Asset_ptr LoadAssetFromFile(const char* file) {
        aiScene* scene = ResourceManager::Scene_ptr(aiImportFile(file, /*flags*/));

        if(!scene.get() == 0) {
            throw std::runtime_error(aiGetErrorString());
        }

        ResourceManager::Asset_ptr asset = ProcessScene(scene);

        aiReleaseImport(scene);

        return asset;
    }

    ResourceManager::Asset_ptr ProcessScene(aiScene* scene) {
        // TODO: process the scene
        ResourceManager::Asset_ptr asset;

        // Do something with scene

        // return asset;
    }
}