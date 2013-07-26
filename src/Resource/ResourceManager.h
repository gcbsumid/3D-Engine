#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Game/Engine.h" 
#include "../Renderer/ModelAsset.h"
#include "../Renderer/Texture.h"

#include <memory>
#include <vector>
#include <string>

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
        Mesh(int);
        ~Mesh();

        // Probably don't need this right now
        void Init(const std::vector<Vertex>* vertices, const std::vector<unsigned int>& indices);

        int mID;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;

        unsigned int mNumIndices; 
        std::string mMaterialName;        
    };

    class ResourceManager {
        typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
        typedef std::weak_ptr<Engine> EnginePtr;
    public:
        static ResourceManagerPtr GetInstance(EnginePtr parent);

        ~ResourceManager() {}

        void SetTextureSharedPointer(std::map<std::string, Texture*> textures);
        void SetMeshSharedPointer(std::vector<Mesh> meshes);

        void LoadAllFiles();
        void Clear();

        void LoadAssetFromFile(const string file); 
        void ProcessScene(aiScene*);

    private:
        // This is shared with the Graphics manager
        std::shared_ptr<std::map<std::string, Texture*> > mTextures;
        std::shared_ptr<std::vector<Mesh> > mMeshes;

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