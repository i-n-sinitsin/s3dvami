// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>

#include "assimp/scene.h"
#include "camera.h"
#include "descriptions/meshes_description.h"
#include "mesh.h"
#include "shaders/shader.h"

namespace s3dvami
{
    class Model
    {
    public:
        Model();
        ~Model();

        bool load(const std::string &fileName);
        void draw(CameraPtr camera);
        void process(float dt);

        bool isLoaded()
        {
            return m_loaded;
        }

        MeshesDescriptionPtr getMeshesDesription() const;

    private:
        bool m_loaded;

        ShaderPtr m_shader;

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
