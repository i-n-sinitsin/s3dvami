// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>

#include "assimp/scene.h"
#include "camera.h"
#include "descriptions/model.h"
#include "mesh.h"
#include "node.h"
#include "shaders/shader.h"
#include "texture.h"

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

        description::ModelPtr getModelDesription() const;

    private:
        bool m_loaded;

        ShaderPtr m_shader;

        description::ModelPtr m_modelDescription;

        glm::mat4 m_globalTransform;
        glm::mat4 m_globalInverseTransform;

        std::vector<MeshPtr> m_meshes;
        NodePtr m_node;
        TextureMgrPtr m_textures;

        glm::mat4 m_translation;
        glm::mat4 m_rotation;
        glm::mat4 m_scale;

        bool loadTextures(const aiScene *scene);
        bool loadMaterials(const aiScene *scene);
        bool loadMeshes(const aiScene *scene);
        bool loadNodes(const aiScene *scene);
        bool loadAnimations(const aiScene *scene);
    };

    using ModelPtr = std::shared_ptr<Model>;

}
