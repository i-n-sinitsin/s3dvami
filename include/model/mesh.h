// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "assimp/scene.h"

#include "shaders/shader.h"

#include "bounding_box.h"
#include "vertex.h"

namespace s3dvami::model
{
    class Mesh
    {
    public:
        explicit Mesh(const aiMesh *mesh);
        ~Mesh();

        void draw(ShaderPtr shader);
        AABBox aabb() const;

        std::string id() const;
        unsigned int verticiesAmount() const;
        unsigned int indicesAmount() const;

    private:
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
