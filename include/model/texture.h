// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "glad/glad.h"

namespace s3dvami
{
    enum class TextureType
    {
        internalRaw,
        internalFile,
        externalFile
    };

    class Texture
    {
    public:
        explicit Texture(const std::string &id, const std::vector<uint8_t> &rawData, unsigned int width, unsigned int height);
        ~Texture();

        std::string id() const;
        unsigned int width() const;
        unsigned int height() const;

    private:
        GLuint m_glId;

        std::string m_id;
        unsigned int m_width;
        unsigned int m_height;
    };

    using TexturePtr = std::shared_ptr<Texture>;
}
