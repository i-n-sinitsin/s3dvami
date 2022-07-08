// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>

#include "glad/glad.h"

namespace s3dvami
{
    class Shader
    {
    public:
        explicit Shader(const std::string &vertShader, const std::string &fragShader);
        ~Shader();

        void use();

    private:
        GLuint m_programId;

        GLuint compile(const std::string &src, GLenum type);
    };

    using ShaderPtr = std::shared_ptr<Shader>;
}
