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
        AABB(const glm::vec3 &v);
        AABB(const aiAABB &aabb);

        AABB operator+(const AABB &o) const;
        AABB operator+(const glm::vec3 &v) const;

        glm::vec3 min() const;
        glm::vec3 max() const;

        glm::vec3 delta() const;
        float minDelta() const;
        float maxDelta() const;

        glm::vec3 center() const;

        void aplayTransformation(const glm::mat4 &m);

    private:
        glm::vec3 m_min;
        glm::vec3 m_max;
    };
}
