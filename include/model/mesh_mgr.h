// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>

#include "model/mesh.h"

namespace s3dvami::model
{
    class MeshMgr
    {
    public:
        MeshMgr();

        AABBox aabb() const;

        void draw(ShaderPtr shader);
        void draw(ShaderPtr shader, unsigned int index);
        void draw(ShaderPtr shader, std::vector<unsigned int> indeces);

        void draw(ShaderPtr shader, const std::string &id);
        void draw(ShaderPtr shader, const std::vector<std::string> &ids);

        void add(const aiMesh *mesh);

        unsigned int meshAmount() const;
        unsigned int verticiesAmount() const;
        unsigned int indeciesAmount() const;

        MeshPtr mesh(unsigned int index);
        const std::vector<MeshPtr> &meshes() const;

    private:
        std::vector<MeshPtr> m_meshes;

        int indexById(const std::string &id); // -1 if not find
    };

    using MeshMgrPtr = std::shared_ptr<MeshMgr>;
}
