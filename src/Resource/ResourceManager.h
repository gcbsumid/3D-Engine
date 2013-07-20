#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Game/Engine.h" 
#include "../Renderer/ModelAsset.h"

#include <memory>
#include <vector>

namespace backlash {
    class Engine;

    struct Vertex {
        glm::vec3 mPosition;    // (x,y,z)
        glm::vec2 mTexCoord;    // (u,v)
        glm::vec3 mNormal;      // (x,y,z)

        Vertex() {};
        Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3 normal) {
            mPosition = pos;
            mTexCoord = tex;
            mNormal = normal;
        }
    };

    struct Mesh {
        struct MeshEntry {
            MeshEntry();
            ~MeshEntry();

            // Probably don't need this right now
            // void Init(const std::vector<Vertex>* vertices, const std::vector<unsigned int>& indices);

            GLuint mVertexBuffer;
            GLuint mIndexBuffer;

            unsigned int mNumIndices; 
            unsigned int mMaterialIndex;
        };

        std::vector<MeshEntry> mEntries;
        std::vector<std::weak_ptr<Texture> > mTextures;
    };

    class ResourceManager {
        typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
        typedef std::weak_ptr<Engine> EnginePtr;
        typedef std::shared_ptr<ModelAsset> AssetPtr;
    public:
        static ResourceManagerPtr GetInstance(EnginePtr parent);

        ~ResourceManager() {}

        void LoadAllFiles();

        AssetPtr LoadAssetFromFile(const char* file); 
        AssetPtr ProcessScene(aiScene*);

    private:
        vector<

        ResourceManager(EnginePtr parent);
        
        static ResourceManagerPtr mInstance;

        ResourceManager(const ResourceManager&);
        void operator=(const ResourceManager&);
    };
}

#endif