// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>

#include "assimp/scene.h"

#include "model/mesh_mgr.h"
#include "model/node_mgr.h"
#include "model/texture_mgr.h"

#include "shaders/shader.h"

#include "camera.h"

namespace s3dvami::model
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

        std::string name() const;
        const MeshMgrPtr meshMgr() const;
        const NodeMgrPtr nodeMgr() const;

    private:
        bool m_loaded;

        ShaderPtr m_shader;

        std::string m_name;
        glm::mat4 m_globalTransform;
        glm::mat4 m_globalInverseTransform;

        MeshMgrPtr m_meshMgr;
        NodeMgrPtr m_nodeMgr;
        TextureMgrPtr m_textureMgr;

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
