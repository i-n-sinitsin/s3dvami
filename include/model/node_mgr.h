// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "assimp/scene.h"

#include "model/mesh_mgr.h"
#include "model/node.h"

#include "shaders/shader.h"

#include "glm/glm.hpp"

namespace s3dvami::model
{
    class NodeMgr
    {
    public:
        NodeMgr(MeshMgrPtr meshMgr);
        NodeMgr(const aiNode *rootNode, MeshMgrPtr meshMgr);

        std::optional<AABB> aabb() const;

        void draw(ShaderPtr shader);

        std::string id() const;
        const std::vector<NodePtr> nodes() const;
        const std::vector<unsigned int> meshes() const;

    private:
        MeshMgrPtr m_meshMgr;

        std::string m_id;
        glm::mat4 m_transformation;

        std::vector<unsigned int> m_meshes;
        std::vector<NodePtr> m_nodes;
    };

    using NodeMgrPtr = std::shared_ptr<NodeMgr>;
}
