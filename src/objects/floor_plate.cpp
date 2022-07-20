// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "objects/floor_plate.h"

#include <iostream>

#include "glad/glad.h"

#include "shaders/simple_frag.h"
#include "shaders/simple_vert.h"

#include "config.h"
namespace s3dvami::objects
{
    FloorPlate::FloorPlate()
        : m_VAO(0)
        , m_VBO(0)
        , m_EBO(0)
        , m_vertices{}
        , m_indices{}
        , m_shader(new Shader(simple_vert, simple_frag))
    {
        float half = defaultfloorPlateSize / 2.0f;

        float dx = defaultfloorPlateSize / static_cast<float>(defaultfloorPartsByAxes);
        float dz = defaultfloorPlateSize / static_cast<float>(defaultfloorPartsByAxes);
        for (unsigned int x = 0; x < defaultfloorPartsByAxes; x++)
        {
            for (unsigned int z = 0; z < defaultfloorPartsByAxes; z++)
            {
                float xmin = -half + dx * x;
                float xmax = -half + dx * (x + 1);
                float zmin = half - dz * z;
                float zmax = half - dz * (z + 1);

                unsigned int startIndex = m_vertices.size();

                m_vertices.push_back({{xmin, 0.0f, zmin}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
                m_vertices.push_back({{xmin, 0.0f, zmax}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
                m_vertices.push_back({{xmax, 0.0f, zmax}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
                m_vertices.push_back({{xmax, 0.0f, zmin}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});

                m_indices.push_back(startIndex + 0);
                m_indices.push_back(startIndex + 1);
                m_indices.push_back(startIndex + 1);
                m_indices.push_back(startIndex + 2);
                m_indices.push_back(startIndex + 2);
                m_indices.push_back(startIndex + 3);
                m_indices.push_back(startIndex + 0);
                m_indices.push_back(startIndex + 3);
            }
        }

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

    FloorPlate::~FloorPlate()
    {
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void FloorPlate::draw(CameraPtr camera)
    {
        m_shader->use();
        m_shader->setUniform("u_projection", camera->projection()->matrix());
        m_shader->setUniform("u_view", camera->view()->matrix());
        m_shader->setUniform("u_model", glm::mat4(1.0f));
        m_shader->setUniform("u_color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        glBindVertexArray(m_VAO);
        glDrawElements(GL_LINES, m_indices.size(), GL_UNSIGNED_INT, (void *)0);
        glBindVertexArray(0);
    }
}
