// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <string>

namespace s3dvami
{
    static const std::string model_vert = R"VERT(
#version 430 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_norm;
layout(location = 2) in vec2 a_tex;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_nodeTransformation;

void main()
{
    mat4 pvm = u_projection * u_view * u_model;
    mat4 pvmnt = pvm * u_nodeTransformation;
    gl_Position = pvm * vec4(a_pos, 1.0f);
}
)VERT";
}
