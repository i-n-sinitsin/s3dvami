// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/texture_mgr.h"

#include <algorithm>
#include <fstream>
#include <iterator>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace s3dvami
{

    TextureMgr::TextureMgr()
        : m_textures{}
    {}

    bool TextureMgr::addByFileName(const std::string &id, const std::string &fileName, bool needCheckId)
    {
        if (needCheckId)
        {
            if (exist(id))
            {
                return true;
            }
        }

        std::ifstream fi(fileName, std::ios::in | std::ios::binary);
        fi.seekg(0, std::ios::end);
        std::vector<uint8_t> buffer(fi.tellg(), '\0');
        fi.seekg(0);
        buffer.insert(buffer.begin(), std::istream_iterator<uint8_t>(fi), std::istream_iterator<uint8_t>());

        return addByFileData(id, buffer, false);
    }

    bool TextureMgr::addByFileData(const std::string &id, const std::vector<uint8_t> &fileData, bool needCheckId)
    {
        if (needCheckId)
        {
            if (exist(id))
            {
                return true;
            }
        }

        stbi_set_flip_vertically_on_load(true);
        /// TODO: use channel from file
        int width = 0;
        int height = 0;
        unsigned char *data = stbi_load_from_memory(fileData.data(), fileData.size(), &width, &height, nullptr, 4);

        if (data == nullptr)
        {
            /// TODO: add log
            return false;
        }

        return addByFileData(id, std::vector<uint8_t>(data, data + width * height * 4), false);
    }

    bool TextureMgr::addByRawData(const std::string & /*id*/, const std::vector<uint8_t> & /*rawData*/, bool /*needCheckId*/)
    {
        return true;
    }

    TexturePtr TextureMgr::texture(unsigned int index)
    {
        /// TODO: add error out
        if (index < m_textures.size())
        {
            return m_textures[index];
        }

        return nullptr;
    }

    const std::vector<TexturePtr> &TextureMgr::textures() const
    {
        return m_textures;
    }

    bool TextureMgr::exist(const std::string &id)
    {
        auto it = std::find_if(m_textures.begin(), m_textures.end(), [=](const TexturePtr texture) {
            return id == texture->id();
        });

        if (it == m_textures.end())
        {
            return false;
        }

        return true;
    }

    /*
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

    bool TextureMgr::loadTexture(const std::string & fileName)
    {
        return true;
    }
*/
}
