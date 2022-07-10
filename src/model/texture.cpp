// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/texture.h"

namespace s3dvami
{

    TextureMgr::TextureMgr()
        : m_loadedTextures{}
    {}

    bool TextureMgr::loadTexture(const aiTexture *tex)
    {
        auto it = std::find_if(m_loadedTextures.begin(), m_loadedTextures.end(), [=](const std::string &x) {
            return x == tex->mFilename.C_Str();
        });

        if (it == m_loadedTextures.end())
        {
            std::shared_ptr<Texture> texture;

            if (tex->mHeight > 0)
            {
                // external format
                //texture = std::make_shared<Texture>(directory + "/" + tex->mFilename.C_Str());
            }
            else
            {
                // internal format
                //unsigned int *startOffset = (unsigned int *)(tex->pcData);
                //unsigned int *endOffset = startOffset + tex->mWidth;
                //std::vector<uint8_t> data(startOffset, endOffset);

                //texture = std::make_shared<Texture>(data);
            }
            //texRaw->initialize(wrap);
            //texture->_textureRaw = texRaw;
            //_textures.push_back(texture);
            //_texturesLoadedNames.push_back(texture->_name);
        }

        return true;
    }

    bool TextureMgr::loadTexture(const std::string & /*fileName*/)
    {
        return true;
    }

}
