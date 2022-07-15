// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <string>

namespace s3dvami
{
    static const std::string model_frag = R"FRAG(
#version 430 core

precision mediump float;

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



out vec4 v_color;

vec4 calc(BaseColor baseColor)
{
    vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    if ( baseColor.used )
    {
        color = baseColor.value;
    }



    return color;
}

vec4 calcDiffuseColor() {
    return calc(u_baseColors[baseColorDiffuse]);
}

void main()
{
    vec4 diffuse = calcDiffuseColor();

    v_color = diffuse;
}
)FRAG";
}
