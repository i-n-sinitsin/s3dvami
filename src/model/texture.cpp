// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/texture.h"

namespace s3dvami
{

    Texture::Texture(const std::string &id, const std::vector<uint8_t> &rawData, unsigned int width, unsigned int height)
        : m_glId(0)
        , m_id(id)
        , m_width(width)
        , m_height(height)
    {
        glGenTextures(1, &m_glId);
        glBindTexture(GL_TEXTURE_2D, m_glId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &rawData[0]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_glId);
    }

    std::string Texture::id() const
    {
        return m_id;
    }

    unsigned int Texture::width() const
    {
        return m_width;
    }

    unsigned int Texture::height() const
    {
        return m_height;
    }

    void Texture::use()
    {
        glBindTexture(GL_TEXTURE_2D, m_glId);
    }

    GLuint Texture::glId() const
    {
        return m_glId;
    }

    void *Texture::glIdPtr()
    {
        return static_cast<void *>(&m_glId);
    }

}
