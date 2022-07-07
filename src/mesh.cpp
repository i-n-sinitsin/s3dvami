// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "mesh.h"

#include "glad/glad.h"

namespace s3dvami
{
    Mesh::Mesh(const aiMesh * /*mesh*/)
        : m_VBO(0)
        , m_EBO(0)
        , m_id()
        , m_vertices{}
        , m_indices{}
    {
        createBuffers();
        fillBuffers();
    }

    void Mesh::createBuffers()
    {
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
    }

    void Mesh::destroyBuffers()
    {}

    void Mesh::fillBuffers()
    {}

}

/*
bool BufferModel3D::createVertex(const std::vector<Vertex3D>& vertices, const std::vector<unsigned int>& indexes) {
    _indexes = indexes;
    for (int i = 0; i < vertices.size(); i++) {
        _data.push_back(vertices[i].position.x);
        _data.push_back(vertices[i].position.y);
        _data.push_back(vertices[i].position.z);
    }
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), &indexes[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, texCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribIPointer(3, 4, GL_INT, sizeof(Vertex3D), (void*)offsetof(Vertex3D, bonesIds));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, bonesWeights));

    return false;
}
*/
