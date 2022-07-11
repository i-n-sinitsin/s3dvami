// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "objects/axes.h"

#include <iostream>

#include "glad/glad.h"

#include "shaders/simple_frag.h"
#include "shaders/simple_vert.h"

#include "config.h"

namespace s3dvami::objects
{
    Axes::Axes(float length, float width)
        : m_VAO(0)
        , m_VBO(0)
        , m_EBO(0)
        , m_vertices{}
        , m_indices{}
        , m_shader(new Shader(simple_vert, simple_frag))
    {
        float half = width / 2.0f;

        // X
        m_vertices.push_back({{0.0f, -half, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{length, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{0.0f, half, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});

        m_vertices.push_back({{0.0f, 0.0f, -half}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{length, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{0.0f, 0.0f, half}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});

        m_indices.insert(m_indices.end(), {0, 1, 2, 3, 4, 5});

        // Y
        m_vertices.push_back({{-half, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{0.0f, length, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{half, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});

        m_vertices.push_back({{0.0f, 0.0f, -half}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{0.0f, length, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{0.0f, 0.0f, half}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});

        m_indices.insert(m_indices.end(), {6, 7, 8, 9, 10, 11});

        // Z
        m_vertices.push_back({{-half, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{0.0f, 0.0f, length}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{half, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});

        m_vertices.push_back({{0.0f, -half, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{0.0f, 0.0f, length}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        m_vertices.push_back({{0.0f, half, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});

        m_indices.insert(m_indices.end(), {12, 13, 14, 15, 16, 17});

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, norm));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tex));

        glBindVertexArray(0);
    }

    Axes::~Axes()
    {
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void Axes::draw(CameraPtr camera)
    {
        m_shader->use();
        m_shader->setUniform("u_projection", camera->getProjection());
        m_shader->setUniform("u_view", camera->getView());
        m_shader->setUniform("u_model", glm::mat4(1.0f));

        glBindVertexArray(m_VAO);

        m_shader->setUniform("u_color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)(0 * sizeof(unsigned int)));

        m_shader->setUniform("u_color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)(6 * sizeof(unsigned int)));

        m_shader->setUniform("u_color", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)(12 * sizeof(unsigned int)));

        glBindVertexArray(0);
    }
}
