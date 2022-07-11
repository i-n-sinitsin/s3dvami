// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/model.h"

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
        , m_meshMgr(new MeshMgr())
        , m_nodeMgr(new NodeMgr())
        , m_textureMgr(new TextureMgr())
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

        m_globalTransform = glm::transpose(glm::make_mat4(&(scene->mRootNode->mTransformation.a1)));
        m_globalInverseTransform = glm::inverse(m_globalTransform);

        AABBox aabb = m_meshMgr->aabb();
        m_name = scene->mName.C_Str();

        // calc scale
        auto scale = defaultModelSize / aabb.maxDelta();
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

        m_nodeMgr->draw(m_shader, m_meshMgr);
    }

    void Model::process(float /*dt*/)
    {
        if (m_loaded)
        {
        }
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

    bool Model::loadTextures(const aiScene *scene)
    {
        bool result = true;

        for (unsigned int i = 0; i < scene->mNumTextures; i++)
        {
            //const aiTexture *aiTex = scene->GetEmbeddedTexture(scene->mTextures[i]->mFilename.C_Str());
            //result = result && m_textures->loadTexture(aiTex);
        }

        return result;
    }

    bool Model::loadMaterials(const aiScene * /*scene*/)
    {
        return true;
    }

    bool Model::loadMeshes(const aiScene *scene)
    {
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            m_meshMgr->add(scene->mMeshes[i]);
        }

        return true;
    }

    bool Model::loadNodes(const aiScene *scene)
    {
        m_nodeMgr = std::make_shared<NodeMgr>(scene->mRootNode);
        return true;
    }

    bool Model::loadAnimations(const aiScene * /*scene*/)
    {
        return true;
    }

}
