// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <string>

namespace s3dvami
{
    static const std::string model_frag = R"FRAG(
#version 430 core

precision mediump float;

// in
in vec2 v_texCoord;

// colors
struct BaseColor
{
    bool used;
    vec4 value;
};

const int baseColorDiffuse = 0;
const int baseColorSpecular = 1;
const int baseColorAmbient = 2;
const int baseColorEmission = 3;
const int baseColorTransporent = 4;
const int baseColorReflective = 5;
const int baseColorAmount = 6;

uniform BaseColor u_baseColors[baseColorAmount];

// textures
const int texTypeNone = 0;
const int texTypeDiffuse = 1;
const int texTypeSpecular = 2;
const int texTypeAmbient = 3;
const int texTypeEmission = 4;
const int texTypeHeight = 5;
const int texTypeNormals = 6;
const int texTypeShininess = 7;
const int texTypeOpacity = 8;
const int texTypeDisplacement = 9;
const int texTypeLightmap = 10;
const int texTypeReflection = 11;
const int texTypeUnknown = 12;
const int texTypeAmount = 13;

const int texOpUnknown = 0;
const int texOpMultiply = 1;
const int texOpAdd = 2;
const int texOpSubstruct = 3;
const int texOpDivide = 4;
const int texOpSmoothAdd = 5;
const int texOpSignedAdd = 6;

const int maxTexturesInOneType = 8;

struct Texture
{
    sampler2D id;
    float blend;
    int operation;
};

struct TexTyped
{
    int amount;
    Texture textures[8];
};

uniform TexTyped u_texTyped[texTypeAmount];


// out
out vec4 v_color;

vec4 calc(BaseColor baseColor, TexTyped texTyped)
{
    vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    if ( baseColor.used )
    {
        color = baseColor.value;
    }

    if ( texTyped.amount > 0 )
    {
        int i = 0;
        while (i < texTyped.amount)
        {
          vec4 localColor = texture(texTyped.textures[i].id, v_texCoord);

          localColor = localColor * texTyped.textures[i].blend;

          if (texTyped.textures[i].operation == 1) {  // T = T1 * T2
            color = color * localColor;
          } else if (texTyped.textures[i].operation == 2) {  // T = T1 + T2
            color = color + localColor;
          } else if (texTyped.textures[i].operation == 3) {  // T = T1 - T2
            color = color - localColor;
          } else if (texTyped.textures[i].operation == 4) {  // T = T1 / T2
            color = color / localColor;
          } else if (texTyped.textures[i].operation == 5) {  // T = (T1 + T2) - (T1 * T2)
            color = (color + localColor) - (color * localColor);
          } else if (texTyped.textures[i].operation == 6) {  // T = T1 + (T2-0.5)
            color = color + (localColor - vec4(0.5));
          }

          i++;
        }
      }

    return color;
}

vec4 calcDiffuseColor() {
    return calc(u_baseColors[baseColorDiffuse], u_texTyped[texTypeDiffuse]);
}

vec4 calcSpecularColor() {
    return calc(u_baseColors[baseColorSpecular], u_texTyped[texTypeSpecular]);
}

void main()
{
    vec4 diffuse = calcDiffuseColor();
    vec4 specular = calcSpecularColor();

    // TODO: think - + or *
    v_color = diffuse + specular;
}
)FRAG";
}
