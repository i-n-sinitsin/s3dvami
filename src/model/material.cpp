// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "model/material.h"

#include <iostream>

namespace s3dvami::model
{

    static const std::map<ColorType, std::tuple<const char *, unsigned int, unsigned int>> colorHelper = {
        {ColorType::diffuse, {AI_MATKEY_COLOR_DIFFUSE}},
        {ColorType::specular, {AI_MATKEY_COLOR_SPECULAR}},
        {ColorType::ambient, {AI_MATKEY_COLOR_AMBIENT}},
        {ColorType::emission, {AI_MATKEY_COLOR_EMISSIVE}},
        {ColorType::transporent, {AI_MATKEY_COLOR_TRANSPARENT}},
        {ColorType::reflective, {AI_MATKEY_COLOR_REFLECTIVE}},
    };

    static const std::map<aiTextureType, TextureType> textureMatches = {
        {aiTextureType_NONE, TextureType::none},
        {aiTextureType_DIFFUSE, TextureType::diffuse},
        {aiTextureType_SPECULAR, TextureType::specular},
        {aiTextureType_AMBIENT, TextureType::ambient},
        {aiTextureType_EMISSIVE, TextureType::emission},
        {aiTextureType_HEIGHT, TextureType::height},
        {aiTextureType_NORMALS, TextureType::normals},
        {aiTextureType_NORMALS, TextureType::shininess},
        {aiTextureType_NORMALS, TextureType::opacity},
        {aiTextureType_NORMALS, TextureType::displacement},
        {aiTextureType_NORMALS, TextureType::lightmap},
        {aiTextureType_NORMALS, TextureType::reflection},
        {aiTextureType_NORMALS, TextureType::unknown},
    };

    Material::Material(const aiMaterial *material, const TextureMgrPtr textureMgr)
        : m_id{}
        , m_twoSided(true)
        , m_wireframe(false)
        , m_colors{
              {ColorType::diffuse, {false, glm::vec4(0.0f)}},
              {ColorType::specular, {false, glm::vec4(0.0f)}},
              {ColorType::ambient, {false, glm::vec4(0.0f)}},
              {ColorType::emission, {false, glm::vec4(0.0f)}},
              {ColorType::transporent, {false, glm::vec4(0.0f)}},
              {ColorType::reflective, {false, glm::vec4(0.0f)}},
          }
        , m_textures{
              {TextureType::none, {}},
              {TextureType::diffuse, {}},
              {TextureType::specular, {}},
              {TextureType::ambient, {}},
              {TextureType::emission, {}},
              {TextureType::height, {}},
              {TextureType::normals, {}},
              {TextureType::shininess, {}},
              {TextureType::opacity, {}},
              {TextureType::displacement, {}},
              {TextureType::lightmap, {}},
              {TextureType::reflection, {}},
              {TextureType::unknown, {}},
          }
    {
        // read name
        {
            aiString tmpStr{};
            if (aiGetMaterialString(material, AI_MATKEY_NAME, &tmpStr) == AI_SUCCESS)
            {
                m_id = std::string(tmpStr.C_Str());
            }
        }

        // read two sided
        {
            ai_int tmpInt{};
            if (aiGetMaterialInteger(material, AI_MATKEY_TWOSIDED, &tmpInt) == AI_SUCCESS)
            {
                m_twoSided = tmpInt != 0;
            }
        }

        // read wireframe
        {
            ai_int tmpInt{};
            if (aiGetMaterialInteger(material, AI_MATKEY_ENABLE_WIREFRAME, &tmpInt) == AI_SUCCESS)
            {
                m_wireframe = tmpInt != 0;
            }
        }

        // read colors
        auto readColor = [material](const char *key, unsigned int type, unsigned int index, glm::vec4 &outColor) -> bool {
            aiColor4t<ai_real> outValue;
            if (aiGetMaterialColor(material, key, type, index, &outValue) == AI_SUCCESS)
            {
                outColor = {outValue.r, outValue.g, outValue.b, outValue.a};
                return true;
            }
            return false;
        };
        for (auto &[key, value] : m_colors)
        {
            auto &t = colorHelper.at(key);
            value.used = readColor(std::get<0>(t), std::get<1>(t), std::get<2>(t), value.value);
        }

        // read textures
        for (const auto &[aiType, type] : textureMatches)
        {
            for (unsigned int i = 0; i < material->GetTextureCount(aiType); i++)
            {
                Texture texture;

                // read texture parameters
                aiString str{};
                ai_real blend{1.0f};
                aiTextureOp texOp{aiTextureOp::aiTextureOp_Multiply};
                material->GetTexture(aiType, i, &str, nullptr, nullptr, &blend, &texOp, nullptr);

                texture.name = str.C_Str();
                texture.blend = blend;

                auto texOpFromAiTexOp = [](const aiTextureOp texOp) {
                    static const std::map<aiTextureOp, TextureOperation> textureOp = {{aiTextureOp_Multiply, TextureOperation::multiply}, {aiTextureOp_Add, TextureOperation::add}, {aiTextureOp_Subtract, TextureOperation::substruct}, {aiTextureOp_Divide, TextureOperation::divide}, {aiTextureOp_SmoothAdd, TextureOperation::smoothAdd}, {aiTextureOp_SignedAdd, TextureOperation::signedAdd}};

                    if (textureOp.find(texOp) == textureOp.end())
                    {
                        /// TODO: add log
                        return TextureOperation::multiply;
                    }

                    return textureOp.at(texOp);
                };

                texture.textureOperation = texOpFromAiTexOp(texOp);

                int index = textureMgr->indexById(texture.name);
                if (index < 0)
                { // texture not found
                    if (!textureMgr->addByFileName(texture.name, texture.name))
                    {
                        /// TODO: add log report about error
                    }
                    index = textureMgr->indexById(texture.name);
                }
                texture.textureIndex = index;

                m_textures.at(type).push_back(texture);
            }
        }

        // not used
        //AI_MATKEY_SHADING_MODEL
        //AI_MATKEY_BLEND_FUNC
        //AI_MATKEY_OPACITY
        //AI_MATKEY_TRANSPARENCYFACTOR
        //AI_MATKEY_BUMPSCALING
        //AI_MATKEY_SHININESS
        //AI_MATKEY_REFLECTIVITY
        //AI_MATKEY_SHININESS_STRENGTH
        //AI_MATKEY_REFRACTI
        //AI_MATKEY_GLOBAL_BACKGROUND_IMAGE
        //AI_MATKEY_GLOBAL_SHADERLANG
        //AI_MATKEY_SHADER_VERTEX
        //AI_MATKEY_SHADER_FRAGMENT
        //AI_MATKEY_SHADER_GEO
        //AI_MATKEY_SHADER_TESSELATION
        //AI_MATKEY_SHADER_PRIMITIVE
        //AI_MATKEY_SHADER_COMPUTE
    }

    std::string Material::id() const
    {
        return m_id;
    }

    bool Material::twoSided() const
    {
        return m_twoSided;
    }

    bool Material::wireframe() const
    {
        return m_wireframe;
    }

    void Material::draw(const ShaderPtr shader, const TextureMgrPtr textureMgr)
    {
        // colors
        for (const auto &[key, value] : m_colors)
        {
            std::string common = "u_baseColors[" + std::to_string(static_cast<unsigned int>(key)) + "].";

            shader->setUniform(common + "used", value.used);
            shader->setUniform(common + "value", value.value);
        }

        // textures
        unsigned int samplerId = 0;
        for (const auto &[key, value] : m_textures)
        {
            std::string common = "u_texTyped[" + std::to_string(static_cast<unsigned int>(key)) + "].";

            shader->setUniform(common + "amount", value.size());

            for (unsigned int i = 0; i < maxTexturesInOneType; i++)
            {
                common = common + "textures[" + std::to_string(i) + "].";
                if (i < value.size())
                {
                    glActiveTexture(GL_TEXTURE0 + samplerId);
                    textureMgr->use(value[i].textureIndex);

                    shader->setUniform(common + "id", samplerId);
                    shader->setUniform(common + "blend", value[i].blend);
                    shader->setUniform(common + "operation", static_cast<unsigned int>(value[i].textureOperation));

                    samplerId++;
                }
            }
        }
    }
}
