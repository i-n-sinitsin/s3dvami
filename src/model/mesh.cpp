// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/mesh.h"

#include "glad/glad.h"

namespace s3dvami::model
{
    Mesh::Mesh(const aiMesh *mesh)
        : m_VAO(0)
        , m_VBO(0)
        , m_EBO(0)
        , m_id()
        , m_vertices{}
        , m_indices{}
        , m_materialIndex{-1}
        , m_aabbox(mesh->mAABB)
    {
        m_id = mesh->mName.C_Str();

        m_vertices.reserve(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            vertex.pos = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};

            if (mesh->mNormals != nullptr)
            {
                vertex.norm = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
            }

            if (mesh->mTextureCoords[0] != nullptr)
            {
                vertex.tex = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
            }
            else
                vertex.tex = {0.0f, 0.0f};

            m_vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                m_indices.push_back(face.mIndices[j]);
            }
        }

        m_materialIndex = mesh->mMaterialIndex;

        createBuffers();
        fillBuffers();
    }

    Mesh::~Mesh()
    {
        destroyBuffers();
    }

    void Mesh::draw(ShaderPtr shader, MaterialMgrPtr materialMgr)
    {
        if (m_materialIndex >= 0)
        {
            materialMgr->draw(shader, materialIndex());
        }

        // TODO: add reading polygon mode from material
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //bool cullFaceTestValue = glIsEnabled(GL_CULL_FACE);
        //glEnable(GL_CULL_FACE);

        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, (void *)0);
        glBindVertexArray(0);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //if (!cullFaceTestValue)
        //    glDisable(GL_CULL_FACE);
    }

    AABB Mesh::aabb() const
    {
        return m_aabbox;
    }

    std::string Mesh::id() const
    {
        return m_id;
    }

    unsigned int Mesh::verticiesAmount() const
    {
        return m_vertices.size();
    }

    unsigned int Mesh::indicesAmount() const
    {
        return m_indices.size();
    }

    int Mesh::materialIndex() const
    {
        return m_materialIndex;
    }

    void Mesh::createBuffers()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
    }

    void Mesh::destroyBuffers()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    void Mesh::fillBuffers()
    {
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, norm));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tex));
        /*
        glEnableVertexAttribArray(3);
        glVertexAttribIPointer(3, 4, GL_INT, sizeof(Vertex3D), (void*)offsetof(Vertex3D, bonesIds));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, bonesWeights));
        */
        glBindVertexArray(0);
    }

}
