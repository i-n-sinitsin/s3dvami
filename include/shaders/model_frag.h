// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <string>

namespace s3dvami
{
    static const std::string model_frag = R"FRAG(
#version 430 core

precision mediump float;
out vec4 v_color;

void main()
{
    v_color = vec4(1.0, 1.0, 1.0, 1.0);
}
)FRAG";
}
