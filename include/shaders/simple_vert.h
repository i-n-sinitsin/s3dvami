// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <string>

namespace s3dvami
{
    static const std::string simple_vert = R"VERT(
#version 430 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_norm;
layout(location = 2) in vec2 a_tex;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform vec4 u_color;

out vec4 v_color;

void main()
{
    v_color = u_color;
    mat4 pvm = u_projection * u_view * u_model;
    gl_Position = pvm * vec4(a_pos, 1.0f);
}
)VERT";
}
