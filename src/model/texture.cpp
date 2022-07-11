// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/texture.h"

namespace s3dvami
{

    Texture::Texture(const std::string & /*id*/, const std::vector<uint8_t> & /*rawData*/, unsigned int /*width*/, unsigned int /*height*/)
    {}

    Texture::~Texture()
    {}

    std::string Texture::id() const
    {
        return "";
    }

}
