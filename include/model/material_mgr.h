// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "assimp/scene.h"

#include "model/material.h"

#include "shaders/shader.h"

namespace s3dvami::model
{
    class MaterialMgr
    {
    public:
        MaterialMgr();

        bool add(const aiMaterial *material);

        MaterialPtr material(unsigned int index);
        const std::vector<MaterialPtr> &materials() const;

    private:
        std::vector<MaterialPtr> m_materials;
    };

    using MaterialMgrPtr = std::shared_ptr<MaterialMgr>;
}
