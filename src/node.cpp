// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "node.h"

#include "glad/glad.h"

#include "glm/gtc/type_ptr.hpp"

namespace s3dvami
{
    Node::Node(const aiNode *node, description::NodePtr nodeDescription)
        : m_nodeDescription(nodeDescription)
        , m_id()
        , m_transformation(1.0f)
        , m_meshes{}
        , m_nodes{}
    {
        m_id = node->mName.C_Str();
        nodeDescription->id = m_id;

        m_transformation = glm::transpose(glm::make_mat4(&(node->mTransformation.a1)));

        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            m_meshes.push_back(node->mMeshes[i]);
            nodeDescription->meshes.push_back(node->mMeshes[i]);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            auto childDescription = std::make_shared<description::Node>();
            auto child = std::make_shared<Node>(node->mChildren[i], childDescription);
            m_nodes.push_back(child);
            nodeDescription->nodes.push_back(childDescription);
        }
    }

    Node::~Node()
    {}

    void Node::draw(ShaderPtr shader, glm::mat4 parentTransformation, const std::vector<MeshPtr> &meshes)
    {
        glm::mat4 currentTransformation = parentTransformation * m_transformation;

        for (auto mesh : m_meshes)
        {
            meshes[mesh]->draw(shader);
        }

        for (const auto &node : m_nodes)
        {
            node->draw(shader, currentTransformation, meshes);
        }
    }
}