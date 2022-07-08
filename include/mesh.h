// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "glad/glad.h"

#include "assimp/scene.h"
#include "bounding_box.h"
#include "descriptions/mesh.h"
#include "vertex.h"

namespace s3dvami
{
    class Mesh
    {
    public:
        explicit Mesh(const aiMesh *mesh, description::MeshPtr meshDescription);
        ~Mesh();

        void draw();
        AABBox getAABB() const;

    private:
        description::MeshPtr m_meshDescription;

        GLuint m_VAO;
        GLuint m_VBO;
        GLuint m_EBO;

        std::string m_id;
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;

        AABBox m_aabbox;

        void createBuffers();
        void destroyBuffers();
        void fillBuffers();
    };

    using MeshPtr = std::shared_ptr<Mesh>;
}
