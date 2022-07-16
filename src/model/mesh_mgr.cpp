// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/mesh_mgr.h"

namespace s3dvami::model
{

    MeshMgr::MeshMgr()
        : m_meshes{}
    {}

    AABB MeshMgr::aabb() const
    {
        AABB aabb;
        for (auto &it : m_meshes)
        {
            aabb = aabb + it->aabb();
        }

        return aabb;
    }

    void MeshMgr::draw(ShaderPtr shader, MaterialMgrPtr materialMgr)
    {
        for (const auto &mesh : m_meshes)
        {
            mesh->draw(shader, materialMgr);
        }
    }

    void MeshMgr::draw(ShaderPtr shader, MaterialMgrPtr materialMgr, unsigned int index)
    {
        /// TODO: add error out
        if (index < m_meshes.size())
        {
            m_meshes[index]->draw(shader, materialMgr);
        }
    }

    void MeshMgr::draw(ShaderPtr shader, MaterialMgrPtr materialMgr, std::vector<unsigned int> indeces)
    {
        for (const auto &index : indeces)
        {
            draw(shader, materialMgr, index);
        }
    }

    void MeshMgr::draw(ShaderPtr shader, MaterialMgrPtr materialMgr, const std::string &id)
    {
        /// TODO: add error out
        int index = indexById(id);
        if (index >= 0)
        {
            draw(shader, materialMgr, index);
        }
    }

    void MeshMgr::draw(ShaderPtr shader, MaterialMgrPtr materialMgr, const std::vector<std::string> &ids)
    {
        for (const auto &id : ids)
        {
            draw(shader, materialMgr, id);
        }
    }

    bool MeshMgr::add(const aiMesh *mesh)
    {
        m_meshes.push_back(std::make_shared<Mesh>(mesh));
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
