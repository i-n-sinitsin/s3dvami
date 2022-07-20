// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace s3dvami
{
    namespace projection
    {
        Base::Base(float width, float height, float near, float far)
            : m_type(Type::base)
            , m_width(width)
            , m_height(height)
            , m_near(near)
            , m_far(far)
            , m_projection(1.0f)
        {}

        const glm::mat4 &Base::matrix() const
        {
            return m_projection;
        }

        Type Base::type() const
        {
            return m_type;
        }

        void Base::setWidth(float width)
        {
            m_width = width;
            updateMatrix();
        }

        void Base::setHeight(float height)
        {
            m_height = height;
            updateMatrix();
        }

        void Base::setNear(float near)
        {
            m_near = near;
            updateMatrix();
        }

        void Base::setFar(float far)
        {
            m_far = far;
            updateMatrix();
        }

        Perspective::Perspective(float fov, float width, float height, float near, float far)
            : Base(width, height, near, far)
            , m_fov(fov)
        {
            updateMatrix();
        }

        void Perspective::setFov(float fov)
        {
            m_fov = fov;
            updateMatrix();
        }

        void Perspective::updateMatrix()
        {
            m_projection = glm::perspective(glm::radians(m_fov), m_width / m_height, m_near, m_far);
        }

        Ortho::Ortho(float width, float height, float near, float far)
            : Base(width, height, near, far)
        {}

        void Ortho::updateMatrix()
        {
            m_projection = glm::ortho(-m_width / 2.0f, m_width / 2.0f, -m_height / 2.0f, m_height / 2.0f, m_near, m_far);
        }

    }

    Camera::Camera(const projection::BasePtr projection)
        : m_projection(projection)
        , m_view(1.0f)
        , m_position(0.0f, 0.0f, 0.0f)
        , m_target(0.0f, 0.0f, 0.0f)
        , m_up(0.0f, 0.0f, 0.0f)
        , m_scale(1.0f)
    {}

    const projection::BasePtr Camera::projection() const
    {
        return m_projection;
    }

    glm::mat4 Camera::view() const
    {
        return m_view;
    }

    void Camera::setView(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
    {
        m_view = glm::lookAt(eye, center, up);
    }

    void Camera::updateMatricies()
    {
        m_view = glm::lookAt(m_position, m_target, m_up);
    }
}
