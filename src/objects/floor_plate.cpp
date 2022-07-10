// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "objects/floor_plate.h"

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
        , m_shader(new Shader(simple_vert, simple_frag))
    {
        float half = defaultfloorPlateSize / 2.0f;
        std::vector<Vertex> m_vertices = {
            {{-half, 0.0f, half}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{-half, 0.0f, -half}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{half, 0.0f, -half}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{half, 0.0f, half}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        };
        std::vector<unsigned int> m_indices = {0, 1, 3, 1, 2, 3};

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
        m_shader->setUniform("u_projection", camera->getProjection());
        m_shader->setUniform("u_view", camera->getView());
        m_shader->setUniform("u_model", glm::mat4(1.0f));

        ///TODO: apply material

        // TODO: add reading polygon mode from material
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //bool cullFaceTestValue = glIsEnabled(GL_CULL_FACE);
        //glEnable(GL_CULL_FACE);
        //bool depthTestValue = glIsEnabled(GL_DEPTH_TEST);
        //glEnable(GL_DEPTH_TEST);

        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //if (!depthTestValue)
        //    glDisable(GL_DEPTH_TEST);
        //if (!cullFaceTestValue)
        //    glDisable(GL_CULL_FACE);
    }
}
