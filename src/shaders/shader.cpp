// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "shaders/shader.h"

#include <iostream>

#include "glad/glad.h"

#include "glm/gtc/type_ptr.hpp"

namespace s3dvami
{
    Shader::Shader(const std::string &vertShader, const std::string &fragShader)
        : m_programId(0)
    {
        GLuint vertShaderId = compile(vertShader, GL_VERTEX_SHADER);
        GLuint fragShaderId = compile(fragShader, GL_FRAGMENT_SHADER);

        m_programId = glCreateProgram();

        /// TODO: add assert for id

        glAttachShader(m_programId, vertShaderId);
        glAttachShader(m_programId, fragShaderId);
        glLinkProgram(m_programId);

        glDeleteShader(vertShaderId);
        glDeleteShader(fragShaderId);

        int status = 0;
        std::string errDescr(1024, ' ');
        glGetProgramiv(m_programId, GL_LINK_STATUS, &status);
        if (!status)
        {
            glGetProgramInfoLog(m_programId, 512, NULL, &errDescr[0]);
            std::cout << errDescr << std::endl;

            glDeleteProgram(m_programId);
            m_programId = 0;
        }
    }

    Shader::~Shader()
    {
        if (m_programId)
        {
            glDeleteProgram(m_programId);
        }
    }

    void Shader::use()
    {
        glUseProgram(m_programId);
    }

    void Shader::setUniform(const std::string &name, const glm::mat4 &m)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
    }

    GLuint Shader::compile(const std::string &src, GLenum type)
    {
        GLuint id = glCreateShader(type);

        /// TODO: add assert for id

        int size = src.size();
        auto shaderSrc = src.c_str();
        glShaderSource(id, 1, &shaderSrc, &size);
        glCompileShader(id);

        GLint status = GL_FALSE;
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            std::string errDescr(maxLength, ' ');
            glGetShaderInfoLog(id, maxLength, &maxLength, &errDescr[0]);
            /// TODO: change cout to log
            std::cout << type << errDescr << std::endl;
            glDeleteShader(id);
        }

        /// TODO: add assert for status

        return id;
    }
}
