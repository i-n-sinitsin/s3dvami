// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/node.h"

#include <iostream>

#include "glm/gtc/type_ptr.hpp"

namespace s3dvami::model
{
    Node::Node(const aiNode *node, MeshMgrPtr meshMgr)
        : m_meshMgr(meshMgr)
        , m_id()
        , m_transformation(1.0f)
        , m_meshes{}
        , m_nodes{}
    {
        m_id = node->mName.C_Str();

        m_transformation = glm::transpose(glm::make_mat4(&(node->mTransformation.a1)));

        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            m_meshes.push_back(node->mMeshes[i]);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            m_nodes.push_back(std::make_shared<Node>(node->mChildren[i], m_meshMgr));
        }
    }

    std::optional<AABB> Node::aabb(const glm::mat4 &parentTransformation) const
    {
        glm::mat4 transformation = parentTransformation * m_transformation;
        std::optional<AABB> result;

        for (const auto &mesh : m_meshes)
        {
            std::optional<AABB> aabb = m_meshMgr->mesh(mesh)->aabb();
            if (aabb.has_value())
            {
                aabb.value().aplayTransformation(transformation);
                if (result.has_value())
                {
                    result = result.value() + aabb.value();
                }
                else
                {
                    result = aabb.value();
                }
            }
        }

        for (const auto &node : m_nodes)
        {
            auto aabb = node->aabb(transformation);
            if (aabb.has_value())
            {
                if (result.has_value())
                {
                    result = result.value() + aabb.value();
                }
                else
                {
                    result = aabb.value();
                }
            }
        }

        return result;
    }

    void Node::draw(ShaderPtr shader, glm::mat4 parentTransformation)
    {
        glm::mat4 nodeTransformation = glm::mat4(1.0f);
        // TODO: update when animations is ready
        nodeTransformation = parentTransformation * m_transformation;
        shader->setUniform("u_nodeTransformation", nodeTransformation);

        m_meshMgr->draw(shader, m_meshes);
        for (const auto &node : m_nodes)
        {
            node->draw(shader, nodeTransformation);
        }
    }

    std::string Node::id() const
    {
        return m_id;
    }

    const std::vector<NodePtr> Node::nodes() const
    {
        return m_nodes;
    }

    const std::vector<unsigned int> Node::meshes() const
    {
        return m_meshes;
    }
}
