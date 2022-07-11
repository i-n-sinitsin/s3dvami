// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/material_mgr.h"

namespace s3dvami::model
{
    MaterialMgr::MaterialMgr()
        : m_materials{}
    {}

    bool MaterialMgr::add(const aiMaterial * /*material*/)
    {
        return true;
    }

    MaterialPtr MaterialMgr::material(unsigned int index)
    {
        /// TODO: add error out
        if (index < m_materials.size())
        {
            return m_materials[index];
        }

        return nullptr;
    }

    const std::vector<MaterialPtr> &MaterialMgr::materials() const
    {
        return m_materials;
    }
}
