// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>

#include "assimp/scene.h"

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
        explicit Texture(const std::string &fileName);
        explicit Texture(const std::vector<uint8_t> &rawFile);

        ~Texture();

    private:
    };

    using TexturePtr = std::shared_ptr<Texture>;

    class TextureMgr
    {
    public:
        TextureMgr();

        bool loadTexture(const aiTexture *tex);
        bool loadTexture(const std::string &fileName);

    private:
        std::vector<std::string> m_loadedTextures;
    };

    using TextureMgrPtr = std::shared_ptr<TextureMgr>;
}
