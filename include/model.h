// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>
#include "mesh.h"
#include "assimp/scene.h"

namespace s3dvami
{
    class Model
    {
    public:
        Model();
        ~Model();

        bool load(const std::string &fileName);
        void draw();
        void process(float dt);

        bool isLoaded()
        {
            return m_loaded;
        }

    private:
        bool m_loaded;

        std::vector<MeshPtr> m_meshes;

        bool loadTextures(const aiScene* scene);
        bool loadMaterials(const aiScene* scene);
        bool loadMeshes(const aiScene* scene);
        bool loadNodes(const aiScene* scene);
        bool loadAnimations(const aiScene* scene);
    };

    using ModelPtr = std::shared_ptr<Model>;

}
