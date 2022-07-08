// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <string>

namespace s3dvami
{
    static const std::string simple_frag = R"FRAG(
#version 430 core

precision mediump float;
out vec4 v_color;

void main()
{
    v_color = vec4(0.8, 0.8, 0.8, 0.5);
}
)FRAG";
}
