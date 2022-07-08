// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>

#include "assimp/scene.h"
#include "glm/glm.hpp"

namespace s3dvami
{
    class AABBox
    {
    public:
        AABBox();
        AABBox(const aiAABB &aabb);

        AABBox operator+(const AABBox &o) const;

        glm::vec3 getDelta() const;
        float getMinDelta() const;
        float getMaxDelta() const;

    private:
        glm::vec3 m_min;
        glm::vec3 m_max;
    };
}