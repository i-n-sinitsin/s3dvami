// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "model/vertex.h"

#include "shaders/shader.h"

#include "camera.h"

namespace s3dvami::objects
{
    class AABB
    {
    public:
        explicit AABB();
        ~AABB();

        void draw(CameraPtr camera);

    private:
        GLuint m_VAO;
        GLuint m_VBO;
        GLuint m_EBO;

        std::optional<glm::vec3> m_min;
        std::optional<glm::vec3> m_max;

        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;

        ShaderPtr m_shader;

        void build();
    };

    using AABBPtr = std::shared_ptr<AABB>;
}
