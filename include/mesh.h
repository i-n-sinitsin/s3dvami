// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "assimp/scene.h"
#include "glad/glad.h"
#include "vertex.h"

namespace s3dvami
{
    class Mesh
    {
    public:
        explicit Mesh(const aiMesh *mesh);

        GLuint m_VBO;
        GLuint m_EBO;

    private:
        std::string m_id;
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;

        void createBuffers();
        void destroyBuffers();
        void fillBuffers();
    };

    using MeshPtr = std::shared_ptr<Mesh>;
}
