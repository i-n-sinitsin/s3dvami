// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "aabb.h"

namespace s3dvami
{
    AABB::AABB()
        : m_min(0.0f)
        , m_max(0.0f)
    {}

    AABB::AABB(const glm::vec3 &v)
        : m_min(v)
        , m_max(v)
    {}

    AABB::AABB(const aiAABB &aabb)
        : m_min(0.0f)
        , m_max(0.0f)
    {
        m_min = glm::vec3(aabb.mMin.x, aabb.mMin.y, aabb.mMin.z);
        m_max = glm::vec3(aabb.mMax.x, aabb.mMax.y, aabb.mMax.z);
    }

    AABB AABB::operator+(const AABB &aabb) const
    {
        AABB result;

        result.m_min = glm::vec3(std::min(m_min.x, aabb.m_min.x), std::min(m_min.y, aabb.m_min.y), std::min(m_min.z, aabb.m_min.z));
        result.m_max = glm::vec3(std::max(m_max.x, aabb.m_max.x), std::max(m_max.y, aabb.m_max.y), std::max(m_max.z, aabb.m_max.z));

        return result;
    }

    glm::vec3 AABB::min() const
    {
        return m_min;
    }

    glm::vec3 AABB::max() const
    {
        return m_max;
    }

    AABB AABB::operator+(const glm::vec3 &v) const
    {
        AABB result;

        result.m_min = glm::vec3(std::min(m_min.x, v.x), std::min(m_min.y, v.y), std::min(m_min.z, v.z));
        result.m_max = glm::vec3(std::max(m_max.x, v.x), std::max(m_max.y, v.y), std::max(m_max.z, v.z));

        return result;
    }

    glm::vec3 AABB::delta() const
    {
        return glm::vec3(m_max.x - m_min.x, m_max.y - m_min.y, m_max.z - m_min.z);
    }

    float AABB::minDelta() const
    {
        auto d = delta();
        return std::min(d.x, std::min(d.y, d.z));
    }

    float AABB::maxDelta() const
    {
        auto d = delta();
        return std::max(d.x, std::max(d.y, d.z));
    }

    glm::vec3 AABB::center() const
    {
        return (m_min + m_max) / 2.0f;
    }

    void AABB::aplayTransformation(const glm::mat4 &m)
    {
        auto newMin = m * glm::vec4(m_min, 1.0f);
        auto newMax = m * glm::vec4(m_max, 1.0f);

        m_min = glm::vec3(std::min(newMin.x, newMax.x), std::min(newMin.y, newMax.y), std::min(newMin.z, newMax.z));
        m_max = glm::vec3(std::max(newMin.x, newMax.x), std::max(newMin.y, newMax.y), std::max(newMin.z, newMax.z));
    }
}
