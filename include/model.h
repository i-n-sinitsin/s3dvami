// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>

#include "assimp/scene.h"
#include "descriptions/meshes_description.h"
#include "mesh.h"

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

        MeshesDescriptionPtr getMeshesDesription() const;

    private:
        bool m_loaded;

        std::vector<MeshPtr> m_meshes;
        MeshesDescriptionPtr m_meshesDescription;

        bool loadTextures(const aiScene *scene);
        bool loadMaterials(const aiScene *scene);
        bool loadMeshes(const aiScene *scene);
        bool loadNodes(const aiScene *scene);
        bool loadAnimations(const aiScene *scene);
    };

    using ModelPtr = std::shared_ptr<Model>;

}
