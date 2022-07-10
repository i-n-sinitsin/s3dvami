// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include "shaders/model_frag.h"
#include "shaders/model_vert.h"

#include "config.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

namespace s3dvami
{

    Model::Model()
        : m_loaded(false)
        , m_shader(new Shader(model_vert, model_frag))
        , m_modelDescription(new description::Model())
        , m_globalTransform(1.0f)
        , m_globalInverseTransform(glm::inverse(glm::mat4(1.0f)))
        , m_meshes{}
        , m_node(nullptr)
        , m_textures(nullptr)
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

        m_modelDescription->name = scene->mName.C_Str();

        m_globalTransform = glm::transpose(glm::make_mat4(&(scene->mRootNode->mTransformation.a1)));
        m_globalInverseTransform = glm::inverse(m_globalTransform);

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

        m_node->draw(m_shader, glm::mat4(1.0f), m_meshes);
    }

    void Model::process(float /*dt*/)
    {
        if (m_loaded)
        {
        }
    }

    description::ModelPtr Model::getModelDesription() const
    {
        return m_modelDescription;
    }

    bool Model::loadTextures(const aiScene *scene)
    {
        bool result = true;
        m_textures = std::make_shared<TextureMgr>();

        for (unsigned int i = 0; i < scene->mNumTextures; i++)
        {
            const aiTexture *aiTex = scene->GetEmbeddedTexture(scene->mTextures[i]->mFilename.C_Str());
            result = result && m_textures->loadTexture(aiTex);
        }

        return result;
    }

    bool Model::loadMaterials(const aiScene * /*scene*/)
    {
        return true;
    }

    bool Model::loadMeshes(const aiScene *scene)
    {
        auto &meshesDescription = m_modelDescription->meshes;
        if (meshesDescription)
        {
            meshesDescription.reset();
        }
        meshesDescription = std::make_shared<description::Meshes>();
        meshesDescription->amount = scene->mNumMeshes;
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            auto meshDescription = std::make_shared<description::Mesh>();
            m_meshes.push_back(std::make_shared<Mesh>(scene->mMeshes[i]));
            meshesDescription->meshes.push_back(meshDescription);

            meshesDescription->verticiesAmount += meshDescription->verticiesAmount;
            meshesDescription->indeciesAmount += meshDescription->indeciesAmount;
        }

        return true;
    }

    bool Model::loadNodes(const aiScene *scene)
    {
        auto &nodeDescription = m_modelDescription->node;
        if (nodeDescription)
        {
            nodeDescription.reset();
        }
        nodeDescription = std::make_shared<description::Node>();
        m_node = std::make_shared<Node>(scene->mRootNode, nodeDescription);
        return true;
    }

    bool Model::loadAnimations(const aiScene * /*scene*/)
    {
        return true;
    }

}
