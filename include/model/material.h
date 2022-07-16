// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <array>
#include <map>
#include <memory>

#include "assimp/scene.h"

#include "model/texture_mgr.h"

#include "shaders/shader.h"

#include "glm/glm.hpp"

namespace s3dvami::model
{
    // max textures of one type (diffuse, specular, etc...)
    // if you change this value, yoy must change shaders and layout
    constexpr int maxTexturesInOneType = 8;

    enum class ColorType
    {
        diffuse,
        specular,
        ambient,
        emission,
        transporent,
        reflective,
        amount
    };

    enum class TextureType
    {
        none,
        diffuse,
        specular,
        ambient,
        emission,
        height,
        normals,
        shininess,
        opacity,
        displacement,
        lightmap,
        reflection,
        unknown,
        amount,
    };

    enum class TextureOperation
    {
        unknown = 0,
        multiply = 1, // T = T1 * T2
        add = 2, // T = T1 + T2
        substruct = 3, // T = T1 - T2
        divide = 4, // T = T1 / T2
        smoothAdd = 5, // T = (T1 + T2) - (T1 * T2)
        signedAdd = 6, // T = T1 + (T2-0.5)
    };

    class Material
    {
    public:
        explicit Material(const aiMaterial *material, const TextureMgrPtr textureMgr);

        std::string id() const;
        bool twoSided() const;
        bool wireframe() const;

        void draw(const ShaderPtr shader, const TextureMgrPtr textureMgr);

    private:
        struct Color
        {
            bool used{false};
            glm::vec4 value{0.0f};
        };

        std::string m_id;
        bool m_twoSided;
        bool m_wireframe;
        std::map<ColorType, Color> m_colors;

        struct Texture
        {
            std::string name{};
            TextureOperation textureOperation{TextureOperation::multiply};
            float blend{1.0f};
            unsigned int textureIndex{};
        };

        std::map<TextureType, std::vector<Texture>> m_textures;
    };

    using MaterialPtr = std::shared_ptr<Material>;
}
