// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "model/texture.h"

namespace s3dvami
{
    class TextureMgr
    {
    public:
        TextureMgr();

        bool addByFileName(const std::string &id, const std::string &fileName, bool needCheckId = true);
        bool addByFileData(const std::string &id, const std::vector<uint8_t> &fileData, bool needCheckId = true);
        bool addByRawData(const std::string &id, const std::vector<uint8_t> &rawData, unsigned int width, unsigned int height, bool needCheckId = true);

        TexturePtr texture(unsigned int index);
        const std::vector<TexturePtr> &textures() const;

        bool exist(const std::string &id);
        int indexById(const std::string &id) const;

        void setCurrentPath(const std::string &path);

    private:
        std::vector<TexturePtr> m_textures;
        std::string m_currentPath;
    };

    using TextureMgrPtr = std::shared_ptr<TextureMgr>;
}
