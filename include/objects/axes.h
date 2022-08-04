// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "model/vertex.h"

#include "shaders/shader.h"

#include "camera.h"

namespace s3dvami::objects
{
    class Axes
    {
    public:
        explicit Axes(float length, float width);
        ~Axes();

        void draw(CameraPtr camera);

        void setLength(float length);
        void setWidth(float width);

    private:
        GLuint m_VAO;
        GLuint m_VBO;
        GLuint m_EBO;

        float m_length;
        float m_width;

        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;

        ShaderPtr m_shader;

        void build();
    };

    using AxesPtr = std::shared_ptr<Axes>;
}
