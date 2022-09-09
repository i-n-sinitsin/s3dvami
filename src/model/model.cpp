// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/model.h"

#include <filesystem>
#include <iostream>

#include <glm/gtx/euler_angles.hpp>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include "shaders/model_frag.h"
#include "shaders/model_vert.h"

#include "config.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

namespace s3dvami::model
{

    Model::Model()
        : m_loaded(false)
        , m_shader(new Shader(model_vert, model_frag))
        , m_name()
        , m_globalTransform(1.0f)
        , m_globalInverseTransform(glm::inverse(glm::mat4(1.0f)))
        , m_textureMgr(new TextureMgr())
        , m_materialMgr(new MaterialMgr(m_textureMgr))
        , m_meshMgr(new MeshMgr(m_materialMgr))
        , m_nodeMgr(new NodeMgr(m_meshMgr))
        , m_translation(0.0f)
        , m_rotation(0.0f)
        , m_scale(1.0f)
        , m_modelTransformation(1.0f)
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

        // save path
        m_textureMgr->setCurrentPath(std::filesystem::path(fileName).parent_path());

        // load
        auto result = loadTextures(scene);
        result = result && loadMaterials(scene);
        result = result && loadMeshes(scene);
        result = result && loadNodes(scene);
        result = result && loadAnimations(scene);

        m_globalTransform = glm::transpose(glm::make_mat4(&(scene->mRootNode->mTransformation.a1)));
        m_globalInverseTransform = glm::inverse(m_globalTransform);

        std::optional<AABB> aabb = m_meshMgr->aabb();
        m_name = scene->mName.C_Str();

        // calc scale
        if (aabb.has_value())
        {
            auto scale = defaultModelSize / aabb.value().maxDelta();
            m_scale = glm::vec3(scale, scale, scale);
        }

        calcModelTransformation();

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
        m_shader->setUniform("u_projection", camera->projection()->matrix());
        m_shader->setUniform("u_view", camera->view()->matrix());
        m_shader->setUniform("u_model", m_modelTransformation);

        m_nodeMgr->draw(m_shader);
    }

    void Model::process(float /*dt*/)
    {
        if (m_loaded)
        {}
    }

    std::string Model::name() const
    {
        return m_name;
    }

    const MeshMgrPtr Model::meshMgr() const
    {
        return m_meshMgr;
    }

    const NodeMgrPtr Model::nodeMgr() const
    {
        return m_nodeMgr;
    }

    const TextureMgrPtr Model::textureMgr() const
    {
        return m_textureMgr;
    }

    std::optional<AABB> Model::aabb() const
    {
        std::optional<AABB> result = m_nodeMgr->aabb();

        if (result.has_value())
        {
            result.value().aplayTransformation(m_modelTransformation);
        }
        return result;
    }

    bool Model::loadTextures(const aiScene *scene)
    {
        bool result = true;

        for (unsigned int i = 0; i < scene->mNumTextures; i++)
        {
            const aiTexture *aiTex = scene->GetEmbeddedTexture(scene->mTextures[i]->mFilename.C_Str());

            std::cout << scene->mTextures[i]->mFilename.C_Str() << std::endl;

            if (aiTex->mHeight > 0)
            {
                // external
                // initialize by filename
                result = result && m_textureMgr->addByFileName(aiTex->mFilename.C_Str(), aiTex->mFilename.C_Str());
            }
            else
            {
                // internal
                unsigned int *startOffset = (unsigned int *)(aiTex->pcData);
                unsigned int *endOffset = startOffset + aiTex->mWidth;
                std::vector<uint8_t> data(startOffset, endOffset);
                // initialize by raw file data
                result = result && m_textureMgr->addByFileData(aiTex->mFilename.C_Str(), data);
            }
        }

        return result;
    }

    bool Model::loadMaterials(const aiScene *scene)
    {
        bool result = true;

        for (unsigned int i = 0; i < scene->mNumMaterials; i++)
        {
            result = result && m_materialMgr->add(scene->mMaterials[i]);
        }

        return result;
    }

    bool Model::loadMeshes(const aiScene *scene)
    {
        bool result = true;
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            result = result && m_meshMgr->add(scene->mMeshes[i]);
        }

        return result;
    }

    bool Model::loadNodes(const aiScene *scene)
    {
        if (scene->mRootNode == nullptr)
        {
            return false;
        }
        m_nodeMgr = std::make_shared<NodeMgr>(scene->mRootNode, m_meshMgr);

        return true;
    }

    bool Model::loadAnimations(const aiScene * /*scene*/)
    {
        return true;
    }

    void Model::calcModelTransformation()
    {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_translation);
        glm::mat4 rotation = glm::yawPitchRoll(m_rotation.x, m_rotation.y, m_rotation.z);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_scale);
        m_modelTransformation = translation * rotation * scale;
    }

}
