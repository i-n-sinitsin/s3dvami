// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <aabb.h>

#include "assimp/scene.h"

#include "model/mesh_mgr.h"

#include "shaders/shader.h"

#include "glm/glm.hpp"

namespace s3dvami::model
{
    class Node;
    using NodePtr = std::shared_ptr<Node>;

    class Node
    {
    public:
        explicit Node(const aiNode *node, const MeshMgrPtr meshMgr);

        std::optional<AABB> aabb(const glm::mat4 &parentTransformation) const;

        void draw(ShaderPtr shader, glm::mat4 parentTransformation);

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
}
