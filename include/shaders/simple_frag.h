// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <string>

namespace s3dvami
{
    static const std::string simple_frag = R"FRAG(
#version 430 core

precision mediump float;

in vec4 v_color;

out vec4 o_color;

void main()
{
    o_color = v_color;
}
)FRAG";
}
