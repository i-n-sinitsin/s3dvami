// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "glad/glad.h"

#include "assimp/scene.h"

#include "model/mesh.h"

#include "descriptions/node.h"

#include "shaders/shader.h"

#include "glm/glm.hpp"

namespace s3dvami
{
    class Node;
    using NodePtr = std::shared_ptr<Node>;

    class Node
    {
    public:
        explicit Node(const aiNode *node, description::NodePtr nodeDescription);
        ~Node();

        void draw(ShaderPtr shader, glm::mat4 parentTransformation, const std::vector<MeshPtr> &meshes);

    private:
        description::NodePtr m_nodeDescription;

        std::string m_id;
        glm::mat4 m_transformation;

        std::vector<unsigned int> m_meshes;
        std::vector<NodePtr> m_nodes;
    };
}
