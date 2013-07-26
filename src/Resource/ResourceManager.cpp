#include "ResourceManager.h"
#include "../Util/util.h"
#include "../Game/Bitmap.h"

#include <cassert>
#include <iostream>

// Global static pointer used to ensure my singleton
std::shared_ptr<backlash::GraphicsManager> backlash::GraphicsManager::mInstance;

const string files[] = {
    "human.blend",
}

static int curTextureID = 0;
static int cur
static std::map<int, string> indexToName;

namespace backlash {

    // Mesh stuff
    Mesh::Mesh(int id) : mID(id) {
        mVertexBuffer = INVALID_OGL_VALUE;
        mIndexBuffer = INVALID_OGL_VALUE;
        mNumIndices = 0;
        mMaterialIndex = 0;
    }

    Mesh::~Mesh() {
        if (mVertexBuffer != INVALID_OGL_VALUE) {
            glDeleteBuffers(1, &mVertexBuffer);
        }

        if (mIndexBuffer != INVALID_OGL_VALUE) {
            glDeleteBuffers(1, &mIndexBuffer);
        }
    }

    void Mesh::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
        mNumIndices = indices.size();

        glGenBuffers(1, &mVertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &mIndexBuffer) ;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mNumIndices, &indices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    // Resource Manager stuff
    ResourceManager::ResourceManager_ptr ResourceManager::GetInstance( 
        ResourceManager::Engine_ptr parent) {
        if (mInstance.get() == 0) {
            mInstance = std::shared_ptr<ResourceManager>(new ResourceManager(parent));
        }
        return mInstance;
    }

    ResourceManager::ResourceManager(ResourceManager::Engine_ptr parent) : 
        mParent(parent) {}

    void ResourceManager::SetTextureSharedPointer(std::map<std::string, Texture*> textures) {
        assert(textures);
        mTextures = std::shared_ptr<std::map<std::string, Texture*> >  (textures);
    }

    void ResourceManager::SetMeshSharedPointer(std::vector<Mesh> meshes) {
        assert(meshes);
        mMeshes = std::shared_ptr<std::vector<Mesh> > (meshes);
    }

    void ResourceManager::LoadAllFiles() {
        for (int i = 0; i < 1; ++i) {
            LoadAssetFromFile(files[i]);
        }
    }

    void ResourceManager::Clear() {
        // Note that before this gets cleared, the pointer values are saved into the global texture
        mLocalTexture.clear();
    }

    void ResourceManager::LoadAssetFromFile(const std::string file) {
        aiScene* scene = ResourceManager::Scene_ptr(aiImportFile(util::ResourcePath(file), 
            aiProcess_GenSmoothNormals | 
            aiProcess_Triangulate | 
            aiProcess_JoinIdenticalVertices));

        if(!scene.get() == 0) {
            throw std::runtime_error(aiGetErrorString());
        }

        InitMaterials(scene, file);
        ProcessScene(scene);

        aiReleaseImport(scene);
    }

    void ResourceManager::ProcessScene(aiScene* scene) {
        // Init each mesh in the scene one by one?
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            const aiMesh* mesh = scene->mMeshes[i];
// !!       // this is a bad assumption 
            InitMesh(i, mesh);
        }

        // Do something with scene
        // return asset;
    }

    void ResourceManager::InitMesh(unsigned int i, const aiMesh* mesh) {
        assert(scene->mNumMaterials == mLocalTexture.size());
        Mesh* meshEntry = new Mesh(mMeshes.size());
        meshEntry->mMaterialName = mLocalTexture.at(mesh->mMaterialIndex);

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            const aiVector3D* pos = &(mesh->mVertices[i]);
            const aiVector3D* normal = &(mesh->mNormals[i]);
            const aiVector3D* texCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i] : &Zero3D;

            Vertex v(glm::vec3(pos->x, pos->y, pos->z),
                     glm::vec2(texCoord->x, texCoord->y),
                     glm::vec3(normal->x, normal->y, normal->z));

            vertices.push_back(v);
        }        

        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            const aiFace& face = mesh->mFaces[i];
            assert(face.mNumIndices == 3); // After being triangulated
            Indices.push_back(Face.mIndices[0]);
            Indices.push_back(Face.mIndices[1]);
            Indices.push_back(Face.mIndices[2]);            
        }

        meshEntry.Init(vertices, indices);

        mGlobalMeshes.push_back(meshEntry);

    }

    void ResourceManager::InitMaterials(aiScene* scene, const std::string& filename) {
        mLocalTexture.clear();

        std::string::size_type slashIndex = filename.find_last_of("/");
        std::string dir;

        if (slashIndex == std::string::npos) {
            dir = ".";
        } else if (slashIndex == 0) {
            dir = "/";
        } else {
            dir = filename.substr(0, slashIndex);
        }

        for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
            const aiMaterial* material = scene->mMaterials[i];

            // std::make_pair(player->GetID(), )
            bool gotTexture = false;
            if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
                aiString path;
                std::string name;

                if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                    gotTexture = true;
                    name = path.data;

                    mLocalTexture.push_back(name);
                    
                    if(mTextures.count(name) == 0) {
                        std::string fullPath = dir + "/" + name;
                        Bitmap bmp = Bitmap::BitmapFromFile(fullPath);
                        bmp.FlipVertically();

                        mTextures.push_back(std::make_pair(name, new Texture(bmp, name)));
                    }
                }
            } 

            if (!gotTexture) {
                mLocalTexture.push_back("white.png");
                if (mTextures.count("white.png") == 0) {
                    Bitmap bmp = Bitmap::BitmapFromFile(utility::ResourcePath("white.png"));
                    bmp.FlipVertically();

                    mTextures.push_back(std::make_pair("white.png", new Texture(bmp, "white.png")));
                }
            }
        }
    }
}