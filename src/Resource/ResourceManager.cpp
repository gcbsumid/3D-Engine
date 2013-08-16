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
#include "../Renderer/Bitmap.h"


// Global static pointer used to ensure my singleton
backlash::ResourceManager* backlash::ResourceManager::mInstance;

const std::string files[] = {
    "phoenix_ugv.md2"
};

static void color4_to_float4(const aiColor4D *c, glm::vec4& f)
{
    f = glm::vec4(c->r, c->g, c->b, c->a);
}

namespace backlash {
    ResourceManager* ResourceManager::GetInstance() {
        if (!mInstance) {
            mInstance = new ResourceManager;
        }
        return mInstance;
    }

    ResourceManager::ResourceManager() {}

    // TODO: Pass a destructor to the shared pointer for when you need to delete the
    //       Texture and Mesh pointers
    void ResourceManager::SetTextureSharedPointer(
        std::shared_ptr<std::map<std::string, Texture*>>& textures)
    {
        mTextures = textures;
    }

    void ResourceManager::SetMeshSharedPointer(
        std::shared_ptr<std::map<int, Mesh*>>& meshes) 
    {
        mMeshes = meshes;
    }

    void ResourceManager::LoadAllFiles() {
        for (int i = 0; i < 1; ++i) {
            LoadAssetFromFile(utility::ResourcePath(files[i]));
        }
    }

    void ResourceManager::Clear() {
        // Note that before this gets cleared, the pointer values are saved into the global texture
        mLocalTexture.clear();
    }

    void ResourceManager::LoadAssetFromFile(const std::string& file) {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(file.c_str(), 
            aiProcess_GenSmoothNormals | 
            aiProcess_Triangulate | 
            aiProcess_JoinIdenticalVertices);

        if (scene) {
            std::cout << "Number of Materials: " << scene->mNumMaterials << std::endl;            
            InitMaterials(scene, file);
            std::cout << "Number of Meshes: " << scene->mNumMeshes << std::endl;            
            ProcessScene(scene);
        } else {
            throw std::runtime_error(importer.GetErrorString());
        }

        importer.FreeScene(); // hopefully this works
    }

    void ResourceManager::ProcessScene(const aiScene* scene) {
        // Init each mesh in the scene one by one?
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            const aiMesh* mesh = scene->mMeshes[i];
            InitMesh(mesh);
        }
    }

    void ResourceManager::InitMesh(const aiMesh* mesh) {
        // assert(scene->mNumMaterials == mLocalTexture.size());
        assert(mMeshes.use_count());

        Mesh* meshEntry = new Mesh(mMeshes->size());
        std::cout << "Adding Mesh with ID: " << meshEntry->mID << std::endl;
        meshEntry->mMaterialName = mLocalTexture.at(mesh->mMaterialIndex);

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            const aiVector3D* pos = &(mesh->mVertices[i]);
            const aiVector3D* normal = &(mesh->mNormals[i]);
            const aiVector3D* texCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;

            Vertex v(glm::vec3(pos->x, pos->y, pos->z),
                     glm::vec2(texCoord->x, texCoord->y),
                     glm::vec3(normal->x, normal->y, normal->z));

            vertices.push_back(v);
        }        

        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            const aiFace& face = mesh->mFaces[i];
            assert(face.mNumIndices == 3); // After being triangulated
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);            
        }

        // meshEntry->mName = mesh->mName.C_Str();
        meshEntry->Init(vertices, indices);

        // std::cout << "Adding Mesh: " << mesh->mName << std::endl;
        // mMeshes->insert(std::make_pair(meshEntry->mName, meshEntry));
        mMeshes->insert(std::make_pair(meshEntry->mID, meshEntry));
    }

    void ResourceManager::InitMaterials(const aiScene* scene, const std::string& filename) {
        assert(mTextures.use_count());
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

            bool gotTexture = false;
            if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
                aiString path;
                std::string name;

                if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                    gotTexture = true;
                    name = path.data;

                    mLocalTexture.push_back(name);
                    
                    if(mTextures->count(name) == 0) {
                        std::string fullPath = dir + "/" + name;
                        std::cout << "Opening file: " << fullPath << std::endl;
                        Bitmap bmp = Bitmap::BitmapFromFile(fullPath);
                        bmp.FlipVertically();

                        std::cout << "Adding Texture: " << name << std::endl;
                        Texture* texture = new Texture(bmp, name);
                        mTextures->insert(std::make_pair(name, texture));
                        SetMaterialData(material, texture);
                    }
                }
            } 

            if (!gotTexture) {
                std::string name = "white.png";
                mLocalTexture.push_back(name);
                if (mTextures->count(name) == 0) {
                    Bitmap bmp = Bitmap::BitmapFromFile(utility::ResourcePath(name));
                    bmp.FlipVertically();

                    std::cout << "Adding Texture: " << name << std::endl;
                    Texture* texture = new Texture(bmp, name);
                    mTextures->insert(std::make_pair(name, texture));
                    SetMaterialData(material, texture);
                }
            }
        }
    }

    void ResourceManager::SetMaterialData(const aiMaterial* material, Texture* texture) {
        glm::vec4 diffuse = glm::vec4(0.8f,0.8f,0.8f,1.0f);
        glm::vec4 ambient = glm::vec4(0.2f,0.2f,0.2f,1.0f);
        glm::vec4 specular = glm::vec4(0.0f,0.0f,0.0f,1.0f);
        // glm::vec4 emission = glm::vec4(0.0f,0.0f,0.0f,1.0f);

        aiColor4D aiDiffuse; 
        aiColor4D aiAmbient;
        aiColor4D aiSpecular;
        // aiColor4D aiEmission;

        if (aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &aiDiffuse)) {
            color4_to_float4(&aiDiffuse, diffuse);
        }
        texture->SetDiffuse(diffuse);

        if (aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &aiAmbient)) {
            color4_to_float4(&aiAmbient, ambient);
        }
        texture->SetAmbient(ambient);

        if (aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &aiSpecular)) {
            color4_to_float4(&aiSpecular, specular);
        }
        texture->SetSpecular(specular);

        // if (aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &aiEmission)) {
        //     color4_to_float4(&aiEmission, emission);
        // }
        // texture->SetEmission(emission);

        float shininess = 0.0;
        unsigned int max;
        aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS, &shininess, &max);
        texture->SetShininess(shininess);        
    }
}