// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/mesh_mgr.h"

namespace s3dvami::model
{

    MeshMgr::MeshMgr(const MaterialMgrPtr materialMgr)
        : m_materialMgr(materialMgr)
        , m_meshes{}
    {}

    std::optional<AABB> MeshMgr::aabb() const
    {
        std::optional<AABB> result;
        for (auto &it : m_meshes)
        {
            if (result.has_value())
            {
                result = result.value() + it->aabb();
            }
            else
            {
                result = it->aabb();
            }
        }

        return result;
    }

    void MeshMgr::draw(ShaderPtr shader)
    {
        for (const auto &mesh : m_meshes)
        {
            mesh->draw(shader);
        }
    }

    void MeshMgr::draw(ShaderPtr shader, unsigned int index)
    {
        /// TODO: add error out
        if (index < m_meshes.size())
        {
            m_meshes[index]->draw(shader);
        }
    }

    void MeshMgr::draw(ShaderPtr shader, std::vector<unsigned int> indeces)
    {
        for (const auto &index : indeces)
        {
            draw(shader, index);
        }
    }

    void MeshMgr::draw(ShaderPtr shader, const std::string &id)
    {
        /// TODO: add error out
        int index = indexById(id);
        if (index >= 0)
        {
            draw(shader, index);
        }
    }

    void MeshMgr::draw(ShaderPtr shader, const std::vector<std::string> &ids)
    {
        for (const auto &id : ids)
        {
            draw(shader, id);
        }
    }

    bool MeshMgr::add(const aiMesh *mesh)
    {
        m_meshes.push_back(std::make_shared<Mesh>(mesh, m_materialMgr));
        return true;
    }

    unsigned int MeshMgr::meshAmount() const
    {
        return m_meshes.size();
    }

    unsigned int MeshMgr::verticiesAmount() const
    {
        unsigned int result = 0;
        for (const auto &mesh : m_meshes)
        {
            result += mesh->verticiesAmount();
        }
        return result;
    }

    unsigned int MeshMgr::indeciesAmount() const
    {
        unsigned int result = 0;
        for (const auto &mesh : m_meshes)
        {
            result += mesh->indicesAmount();
        }
        return result;
    }

    MeshPtr MeshMgr::mesh(unsigned int index)
    {
        /// TODO: add error out
        if (index < m_meshes.size())
        {
            return m_meshes[index];
        }

        return nullptr;
    }

    const std::vector<MeshPtr> &MeshMgr::meshes() const
    {
        return m_meshes;
    }

    int MeshMgr::indexById(const std::string &id)
    {
        /// TODO: add error out

        int result = 0;
        for (const auto &mesh : m_meshes)
        {
            if (mesh->id() == id)
            {
                return result;
            }
            result++;
        }

        return -1;
    }

}
