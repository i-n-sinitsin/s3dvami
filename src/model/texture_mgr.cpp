// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/texture_mgr.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include "stb_image.h"

namespace s3dvami::model
{

    TextureMgr::TextureMgr()
        : m_textures{}
        , m_currentPath{}
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

        // Replace the slashes
        std::string fixedFileName = fileName;
        std::replace(fixedFileName.begin(), fixedFileName.end(), '\\', '/');
        std::string path = std::filesystem::path(m_currentPath + "/" + fixedFileName).make_preferred();
        /// TODO: add log
        if (!std::filesystem::exists(path))
        {
            return false;
        }

        std::ifstream fi(path, std::ios::in | std::ios::binary);
        fi.unsetf(std::ios::skipws);
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
        unsigned char *rawData = stbi_load_from_memory(fileData.data(), fileData.size(), &width, &height, nullptr, 4);

        if (rawData == nullptr)
        {
            /// TODO: add log
            std::cout << "Error load image: " << stbi_failure_reason() << std::endl;

            return false;
        }

        bool result = addByRawData(id, std::vector<uint8_t>(rawData, rawData + width * height * 4), width, height, false);
        stbi_image_free(rawData);
        return result;
    }

    bool TextureMgr::addByRawData(const std::string &id, const std::vector<uint8_t> &rawData, unsigned int width, unsigned int height, bool needCheckId)
    {
        if (needCheckId)
        {
            if (exist(id))
            {
                return true;
            }
        }

        auto texture = std::make_shared<Texture>(id, rawData, width, height);
        m_textures.push_back(texture);
        return true;
    }

    unsigned int TextureMgr::amount() const
    {
        return m_textures.size();
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

    int TextureMgr::indexById(const std::string &id) const
    {
        /// TODO: add error out
        for (unsigned int i = 0; i < m_textures.size(); i++)
        {
            if (id == m_textures[i]->id())
            {
                return i;
            }
        }

        return -1;
    }

    void TextureMgr::setCurrentPath(const std::string &path)
    {
        m_currentPath = path;
    }

    void TextureMgr::use(const std::string &id)
    {
        use(indexById(id));
    }

    void TextureMgr::use(unsigned int id)
    {
        if (id >= m_textures.size())
        {
            /// TODO: add log
        }
        m_textures[id]->use();
    }
}
