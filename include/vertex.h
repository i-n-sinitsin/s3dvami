// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include "glm/glm.hpp"

namespace s3dvami
{
    struct Vertex
    {
        glm::vec3 pos{};
        glm::vec3 norm{};
        glm::vec2 tex{};
    };
}
