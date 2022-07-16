// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>

#include "assimp/scene.h"

#include "glm/glm.hpp"

namespace s3dvami
{
    class AABB
    {
    public:
        AABB();
        AABB(const aiAABB &aabb);

        AABB operator+(const AABB &o) const;

        glm::vec3 delta() const;
        float minDelta() const;
        float maxDelta() const;

        glm::vec3 center() const;

    private:
        glm::vec3 m_min;
        glm::vec3 m_max;
    };
}
