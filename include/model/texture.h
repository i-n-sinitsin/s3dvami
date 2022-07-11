// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>

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
        Texture();

        std::string id() const;

        //explicit Texture(const std::string &fileName);
        //explicit Texture(const std::vector<uint8_t> &rawFile);

        //~Texture();

    private:
    };

    using TexturePtr = std::shared_ptr<Texture>;
}
