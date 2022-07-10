// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "bounding_box.h"

namespace s3dvami
{
    AABBox::AABBox()
        : m_min(0.0f)
        , m_max(0.0f)
    {}

    AABBox::AABBox(const aiAABB &aabb)
        : m_min(0.0f)
        , m_max(0.0f)
    {
        m_min = glm::vec3(aabb.mMin.x, aabb.mMin.y, aabb.mMin.z);
        m_max = glm::vec3(aabb.mMax.x, aabb.mMax.y, aabb.mMax.z);
    }

    AABBox AABBox::operator+(const AABBox &aabb) const
    {
        AABBox result;

        result.m_min = glm::vec3(std::min(m_min.x, aabb.m_min.x), std::min(m_min.y, aabb.m_min.y), std::min(m_min.z, aabb.m_min.z));
        result.m_max = glm::vec3(std::max(m_max.x, aabb.m_max.x), std::max(m_max.y, aabb.m_max.y), std::max(m_max.z, aabb.m_max.z));

        return result;
    }

    glm::vec3 AABBox::delta() const
    {
        return glm::vec3(m_max.x - m_min.x, m_max.y - m_min.y, m_max.z - m_min.z);
    }

    float AABBox::minDelta() const
    {
        auto d = delta();
        return std::min(d.x, std::min(d.y, d.z));
    }

    float AABBox::maxDelta() const
    {
        auto d = delta();
        return std::max(d.x, std::max(d.y, d.z));
    }

    glm::vec3 AABBox::center() const
    {
        return (m_min + m_max) / 2.0f;
    }
}
