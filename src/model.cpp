// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "imgui.h"

namespace s3dvami
{

    Model::Model()
        : m_loaded(false)
    {}

    Model::~Model()
    {}

    bool Model::load(const std::string &fileName)
    {
        Assimp::Importer importer;

        auto scene = importer.ReadFile(fileName, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenBoundingBoxes);
        if (!scene)
        {
            m_loaded = false;
            return false;
        }

        auto result = loadTextures();
        result = result && loadMaterials();
        result = result && loadMeshes();
        result = result && loadNodes();
        result = result && loadAnimations();

        m_loaded = result;
        return result;
    }

    void Model::draw()
    {
        if (!m_loaded)
        {
            return;
        }

        /// TODO: draw model
    }

    void Model::process(float /*dt*/)
    {
        if (m_loaded)
        {
        }
    }

    bool Model::loadTextures()
    {
        return true;
    }

    bool Model::loadMaterials()
    {
        return true;
    }

    bool Model::loadMeshes()
    {
        return true;
    }

    bool Model::loadNodes()
    {
        return true;
    }

    bool Model::loadAnimations()
    {
        return true;
    }

}
