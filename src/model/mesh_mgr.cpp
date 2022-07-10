// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/mesh_mgr.h"

namespace s3dvami::model
{

    MeshMgr::MeshMgr()
        : m_meshes{}
    {}

    AABBox MeshMgr::aabb() const
    {
        AABBox aabb;
        for (auto &it : m_meshes)
        {
            aabb = aabb + it->aabb();
        }

        return aabb;
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

    void MeshMgr::add(const aiMesh *mesh)
    {
        m_meshes.push_back(std::make_shared<Mesh>(mesh));
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
