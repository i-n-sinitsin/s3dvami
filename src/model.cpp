// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "config.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "shaders/model_frag.h"
#include "shaders/model_vert.h"

namespace s3dvami
{

    Model::Model()
        : m_loaded(false)
        , m_shader(new Shader(model_vert, model_frag))
        , m_modelDescription(new ModelDescription())
        , m_meshes{}
        , m_translation(1.0f)
        , m_rotation(1.0f)
        , m_scale(1.0f)
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

        AABBox aabb;
        for (auto &it : m_meshes)
        {
            aabb = aabb + it->getAABB();
        }

        // calc scale
        auto scale = defaultModelSize / aabb.getMaxDelta();
        m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));

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
        auto model = m_translation * m_rotation * m_scale;
        m_shader->setUniform("u_model", model);
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

    ModelDescriptionPtr Model::getModelDesription() const
    {
        return m_modelDescription;
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
        auto &meshesDescr = m_modelDescription->meshes;
        if (meshesDescr)
        {
            meshesDescr.reset();
        }
        meshesDescr = std::make_shared<MeshesDescription>();
        meshesDescr->amount = scene->mNumMeshes;
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            auto meshDescription = std::make_shared<MeshDescription>();
            m_meshes.push_back(std::make_shared<Mesh>(scene->mMeshes[i], meshDescription));
            meshesDescr->meshes.push_back(meshDescription);

            meshesDescr->verticiesAmount += meshDescription->verticiesAmount;
            meshesDescr->indeciesAmount += meshDescription->indeciesAmount;
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
