// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "imgui.h"
#include "shaders/model_frag.h"
#include "shaders/model_vert.h"

namespace s3dvami
{

    Model::Model()
        : m_loaded(false)
        , m_shader(new Shader(model_vert, model_frag))
        , m_meshes{}
        , m_meshesDescription(nullptr)
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

        auto result = loadTextures(scene);
        result = result && loadMaterials(scene);
        result = result && loadMeshes(scene);
        result = result && loadNodes(scene);
        result = result && loadAnimations(scene);

        m_loaded = result;
        return result;
    }

    void Model::draw(CameraPtr camera)
    {
        if (!m_loaded)
        {
            return;
        }

        m_shader->use();
        m_shader->setUniform("u_projection", camera->getProjection());
        m_shader->setUniform("u_view", camera->getView());

        m_shader->setUniform("u_model", glm::mat4(1.0f));
        /// TODO: draw model

        for (const auto &it : m_meshes)
        {
            it->draw();
        }
    }

    void Model::process(float /*dt*/)
    {
        if (m_loaded)
        {
        }
    }

    MeshesDescriptionPtr Model::getMeshesDesription() const
    {
        return m_meshesDescription;
    }

    bool Model::loadTextures(const aiScene * /*scene*/)
    {
        return true;
    }

    bool Model::loadMaterials(const aiScene * /*scene*/)
    {
        return true;
    }

    bool Model::loadMeshes(const aiScene *scene)
    {
        if (m_meshesDescription)
        {
            m_meshesDescription.reset();
        }
        m_meshesDescription = std::make_shared<MeshesDescription>();
        m_meshesDescription->amount = scene->mNumMeshes;
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            auto meshDescription = std::make_shared<MeshDescription>();
            m_meshes.push_back(std::make_shared<Mesh>(scene->mMeshes[i], meshDescription));
            m_meshesDescription->meshes.push_back(meshDescription);

            m_meshesDescription->verticiesAmount += meshDescription->verticiesAmount;
            m_meshesDescription->indeciesAmount += meshDescription->indeciesAmount;
        }

        return true;
    }

    bool Model::loadNodes(const aiScene * /*scene*/)
    {
        return true;
    }

    bool Model::loadAnimations(const aiScene * /*scene*/)
    {
        return true;
    }

}
