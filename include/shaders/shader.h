// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>

#include "glad/glad.h"

#include "glm/glm.hpp"

namespace s3dvami
{
    class Shader
    {
    public:
        explicit Shader(const std::string &vertShader, const std::string &fragShader);
        ~Shader();

        void use();

        void setUniform(const std::string &name, const glm::mat4 &m);

        void setUniform(const std::string &name, const glm::vec4 &v);
        void setUniform(const std::string &name, const glm::vec3 &v);
        void setUniform(const std::string &name, const glm::vec2 &v);

    private:
        GLuint m_programId;

        GLuint compile(const std::string &src, GLenum type);
    };

    using ShaderPtr = std::shared_ptr<Shader>;
}
