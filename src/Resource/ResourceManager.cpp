// Assimp Library
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

// GLM Library
#include <glm/glm.hpp>

// Standard Library
#include <cassert>
#include <iostream>

// Backlash Library
#include "ResourceManager.h"
#include "../Util/util.h"
#include "../Game/Bitmap.h"


// Global static pointer used to ensure my singleton
backlash::ResourceManager* backlash::ResourceManager::mInstance;

const string files[] = {
    "human.blend"
};

static int curTextureID = 0;

static void color4_to_float4(const Assimp::aiColor4D *c, float f[4])
{
    f[0] = c->r;
    f[1] = c->g;
    f[2] = c->b;
    f[3] = c->a;
}

namespace backlash {
    ResourceManager::ResourceManager* ResourceManager::GetInstance(Engine* parent) {
        if (mInstance.get() == 0) {
            mInstance = new ResourceManager{parent};
        }
        return mInstance;
    }

    ResourceManager::ResourceManager(Engine* parent) : 
        mParent{parent} {}

    // TODO: Pass a destructor to the shared pointer for when you need to delete the
    //       Texture and Mesh pointers
    void ResourceManager::SetTextureSharedPointer(std::map<std::string, Texture*>* textures) {
        assert(textures);
        mTextures = std::shared_ptr<std::map<std::string, Texture*>>(textures);
    }

    void ResourceManager::SetMeshSharedPointer(std::map<std::string, Mesh*>* meshes) {
        assert(meshes);
        mMeshes = std::shared_ptr<std::map<std::string, Mesh*>> (meshes);
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

    void ResourceManager::LoadAssetFromFile(const std::string& file) {
        Assimp::Importer importer;

        Assimp::aiScene* scene = importer.ReadFile(file.c_str(), 
            Assimp::aiProcess_GenSmoothNormals | 
            Assimp::aiProcess_Triangulate | 
            Assimp::aiProcess_JoinIdenticalVertices);

        if (scene) {
            InitMaterials(scene, file);
            ProcessScene(scene);
        } else {
            throw std::runtime_error(importer.GetErrorString());
        }

        importer.FreeScene(scene); // hopefully this works
    }

    void ResourceManager::ProcessScene(Assimp::aiScene* scene) {
        // Init each mesh in the scene one by one?
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            const Assimp::aiMesh* mesh = scene->mMeshes[i];
            InitMesh(mesh);
        }
    }

    void ResourceManager::InitMesh(Assimp::aiMesh* mesh) {
        assert(scene->mNumMaterials == mLocalTexture.size());
        assert(mMeshes);

        Mesh* meshEntry = new Mesh(mMeshes.size());
        meshEntry->mMaterialName = mLocalTexture.at(mesh->mMaterialIndex);

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        const Assimp::aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            const Assimp::aiVector3D* pos = &(mesh->mVertices[i]);
            const Assimp::aiVector3D* normal = &(mesh->mNormals[i]);
            const Assimp::aiVector3D* texCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i] : &Zero3D;

            Vertex v(glm::vec3(pos->x, pos->y, pos->z),
                     glm::vec2(texCoord->x, texCoord->y),
                     glm::vec3(normal->x, normal->y, normal->z));

            vertices.push_back(v);
        }        

        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            const Assimp::aiFace& face = mesh->mFaces[i];
            assert(face.mNumIndices == 3); // After being triangulated
            indices.push_back(Face.mIndices[0]);
            indices.push_back(Face.mIndices[1]);
            indices.push_back(Face.mIndices[2]);            
        }

        meshEntry.mName = mesh->mName.C_Str();
        meshEntry.Init(vertices, indices);

        mMeshes.push_back(meshEntry.mName, meshEntry);
    }

    void ResourceManager::InitMaterials(Assimp::aiScene* scene, const std::string& filename) {
        assert(mTextures);
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
            const Assimp::aiMaterial* material = scene->mMaterials[i];

            // std::make_pair(player->GetID(), )
            bool gotTexture = false;
            if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
                Assimp::aiString path;
                std::string name;

                if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                    gotTexture = true;
                    name = path.data;

                    mLocalTexture.push_back(name);
                    
                    if(mTextures.count(name) == 0) {
                        std::string fullPath = dir + "/" + name;
                        Bitmap bmp = Bitmap::BitmapFromFile(fullPath);
                        bmp.FlipVertically();

                        Texture* texture = new Texture(bmp, name);
                        mTextures.push_back(std::make_pair(name, texture));
                        SetMaterialData(material, texture);
                    }
                }
            } 

            if (!gotTexture) {
                std::string name = "white.png";
                mLocalTexture.push_back(name);
                if (mTextures.count(name) == 0) {
                    Bitmap bmp = Bitmap::BitmapFromFile(utility::ResourcePath(name));
                    bmp.FlipVertically();

                    Texture* texture = new Texture(bmp, name);
                    mTextures.push_back(std::make_pair(name, texture));
                    SetMaterialData(material, texture);
                }
            }
        }
    }

    void ResourceManager::SetMaterialData(Assimp::aiMaterial* material, Texture* texture) {
        glm::vec4 diffuse = glm::vec4(0.8f,0.8f,0.8f,1.0f);
        glm::vec4 ambient = glm::vec4(0.2f,0.2f,0.2f,1.0f);
        glm::vec4 specular = glm::vec4(0.0f,0.0f,0.0f,1.0f);
        // glm::vec4 emission = glm::vec4(0.0f,0.0f,0.0f,1.0f);

        Assimp::aiColor4D aiDiffuse; 
        Assimp::aiColor4D aiAmbient;
        Assimp::aiColor4D aiSpecular;
        // Assimp::aiColor4D aiEmission;

        if (Assimp::aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &aiDiffuse)) {
            color4_to_float4(&aiDiffuse, diffuse);
        }
        texture.SetDiffuse(diffuse);

        if (Assimp::aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &aiAmbient)) {
            color4_to_float4(&aiAmbient, ambient);
        }
        texture.SetAmbient(ambient);

        if (Assimp::aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &aiSpecular)) {
            color4_to_float4(&aiSpecular, specular);
        }
        texture.SetSpecular(specular);

        // if (Assimp::aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &aiEmission)) {
        //     color4_to_float4(&aiEmission, emission);
        // }
        // texture.SetEmission(emission);

        float shininess 0.0;
        unsigned int max;
        Assimp::aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
        texture.SetShininess(shininess);        
    }
}