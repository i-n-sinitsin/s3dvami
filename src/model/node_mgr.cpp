// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/node_mgr.h"

#include "glm/gtc/type_ptr.hpp"

namespace s3dvami::model
{

    NodeMgr::NodeMgr(MeshMgrPtr meshMgr)
        : m_meshMgr(meshMgr)
        , m_id()
        , m_transformation(1.0f)
        , m_meshes{}
        , m_nodes{}
    {}

    NodeMgr::NodeMgr(const aiNode *rootNode, MeshMgrPtr meshMgr)
        : m_meshMgr(meshMgr)
        , m_id()
        , m_transformation(1.0f)
        , m_meshes{}
        , m_nodes{}
    {
        m_id = rootNode->mName.C_Str();

        m_transformation = glm::transpose(glm::make_mat4(&(rootNode->mTransformation.a1)));

        for (unsigned int i = 0; i < rootNode->mNumMeshes; i++)
        {
            m_meshes.push_back(rootNode->mMeshes[i]);
        }

        for (unsigned int i = 0; i < rootNode->mNumChildren; i++)
        {
            m_nodes.push_back(std::make_shared<Node>(rootNode->mChildren[i], meshMgr));
        }
    }

    std::optional<AABB> NodeMgr::aabb() const
    {
        std::optional<AABB> result;

        for (const auto &node : m_nodes)
        {
            auto aabb = node->aabb(m_transformation);
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

    void NodeMgr::draw(ShaderPtr shader)
    {
        for (const auto &node : m_nodes)
        {
            node->draw(shader, m_transformation);
        }
    }

    std::string NodeMgr::id() const
    {
        return m_id;
    }

    const std::vector<NodePtr> NodeMgr::nodes() const
    {
        return m_nodes;
    }

    const std::vector<unsigned int> NodeMgr::meshes() const
    {
        return m_meshes;
    }

}
