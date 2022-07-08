// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <string>

namespace s3dvami
{
    static const std::string model_vert = R"
    #version 430 core

    layout(location = 0) in vec3 a_pos;
    layout(location = 1) in vec3 a_Norm;
    layout(location = 2) in vec2 a_tex;
    uniform mat4 u_model;
    uniform mat4 u_globalModel;
    uniform mat4 u_view;
    uniform mat4 u_projection;

    void main()
    {
        mat4 pvm = u_projection * u_view * u_model;
        gl_Position = pvm * vec4(a_pos, 1.0f);
    }
    ";
}
