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
            , m_needUpdateMatrix(true)
        {}

        const glm::mat4 &Base::matrix()
        {
            if (m_needUpdateMatrix)
            {
                updateMatrix();
                m_needUpdateMatrix = false;
            }
            return m_projection;
        }

        Type Base::type() const
        {
            return m_type;
        }

        void Base::setWidth(float width)
        {
            m_width = width;
            m_needUpdateMatrix = true;
        }

        void Base::setHeight(float height)
        {
            m_height = height;
            m_needUpdateMatrix = true;
        }

        void Base::setNear(float near)
        {
            m_near = near;
            m_needUpdateMatrix = true;
        }

        void Base::setFar(float far)
        {
            m_far = far;
            m_needUpdateMatrix = true;
        }

        Perspective::Perspective(float fov, float width, float height, float near, float far)
            : Base(width, height, near, far)
            , m_fov(fov)
        {}

        void Perspective::setFov(float fov)
        {
            m_fov = fov;
            m_needUpdateMatrix = true;
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

    namespace view
    {
        Base::Base(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &up)
            : m_type(Type::base)
            , m_needUpdateMatrix(true)
            , m_view(1.0f)
            , m_position(position)
            , m_target(target)
            , m_up(glm::normalize(up))
        {}

        Base::Base(const BasePtr &view)
            : Base(view->position(), view->target(), view->up())
        {}

        Type Base::type() const
        {
            return m_type;
        }

        const glm::mat4 &Base::matrix()
        {
            if (m_needUpdateMatrix)
            {
                updateMatrix();
            }
            return m_view;
        }

        void Base::setPosition(const glm::vec3 &position)
        {
            m_position = position;
            m_needUpdateMatrix = true;
        }

        void Base::setTarget(const glm::vec3 &target)
        {
            m_target = target;
            m_needUpdateMatrix = true;
        }

        void Base::setUp(const glm::vec3 &up)
        {
            m_up = glm::normalize(up);
            m_needUpdateMatrix = true;
        }

        glm::vec3 Base::position() const
        {
            return m_position;
        }

        glm::vec3 Base::target() const
        {
            return m_target;
        }

        glm::vec3 Base::up() const
        {
            return m_up;
        }

        void Base::updateMatrix()
        {
            m_view = glm::lookAt(m_position, m_target, m_up);
            m_needUpdateMatrix = false;
        }

        Free::Free()
            : Base({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f})
        {}

        Free::Free(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &up)
            : Base(position, target, up)
        {}

        Free::Free(const BasePtr &view)
            : Base(view)
        {}

        void Free::moveLeft(float distance)
        {
            glm::vec3 direction = m_target - m_position;
            glm::vec3 right = glm::normalize(glm::cross(direction, m_up));

            m_position = m_position - distance * right;
            m_target = m_target - distance * right;

            m_needUpdateMatrix = true;
        }

        void Free::moveRight(float distance)
        {
            glm::vec3 direction = m_target - m_position;
            glm::vec3 right = glm::normalize(glm::cross(direction, m_up));

            m_position = m_position + distance * right;
            m_target = m_target + distance * right;

            m_needUpdateMatrix = true;
        }

        void Free::moveUp(float distance)
        {
            glm::vec3 direction = m_target - m_position;
            glm::vec3 right = glm::cross(direction, m_up);
            glm::vec3 up = glm::normalize(glm::cross(right, direction));

            m_position = m_position + distance * up;
            m_target = m_target + distance * up;

            m_needUpdateMatrix = true;
        }

        void Free::moveDown(float distance)
        {
            glm::vec3 direction = m_target - m_position;
            glm::vec3 right = glm::cross(direction, m_up);
            glm::vec3 up = glm::normalize(glm::cross(right, direction));

            m_position = m_position - distance * up;
            m_target = m_target - distance * up;

            m_needUpdateMatrix = true;
        }

        void Free::moveFront(float distance)
        {
            glm::vec3 direction = glm::normalize(m_target - m_position);

            m_position = m_position + distance * direction;
            m_target = m_target + distance * direction;

            m_needUpdateMatrix = true;
        }

        void Free::moveBack(float distance)
        {
            glm::vec3 direction = glm::normalize(m_target - m_position);

            m_position = m_position - distance * direction;
            m_target = m_target - distance * direction;

            m_needUpdateMatrix = true;
        }

        void Free::turnLeft(float /*distance*/)
        {}

        void Free::turnRight(float /*distance*/)
        {}

        void Free::turnUp(float /*distance*/)
        {}

        void Free::turnDown(float /*distance*/)
        {}

        Orbit::Orbit()
            : Base({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f})
        {}

        Orbit::Orbit(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &up)
            : Base(position, target, up)
        {}

        Orbit::Orbit(const BasePtr &view)
            : Base(view)
        {}

        void Orbit::moveLeft(float distance)
        {
            glm::vec3 relativePosition = m_target - m_position;
            glm::vec3 direction = relativePosition;
            glm::vec3 right = glm::normalize(glm::cross(direction, m_up));

            float length = glm::length(direction);
            relativePosition = glm::normalize(relativePosition + distance * right) * length;

            m_position = m_target - relativePosition;

            m_needUpdateMatrix = true;
        }

        void Orbit::moveRight(float distance)
        {
            glm::vec3 relativePosition = m_target - m_position;
            glm::vec3 direction = relativePosition;
            glm::vec3 right = glm::normalize(glm::cross(direction, m_up));

            float length = glm::length(direction);
            relativePosition = glm::normalize(relativePosition - distance * right) * length;

            m_position = m_target - relativePosition;

            m_needUpdateMatrix = true;
        }

        void Orbit::moveUp(float distance)
        {
            glm::vec3 relativePosition = m_target - m_position;
            glm::vec3 direction = relativePosition;
            glm::vec3 right = glm::cross(direction, m_up);
            glm::vec3 up = glm::normalize(glm::cross(right, direction));

            float length = glm::length(direction);
            relativePosition = glm::normalize(relativePosition - distance * up) * length;

            m_position = m_target - relativePosition;

            m_up = up;

            m_needUpdateMatrix = true;
        }

        void Orbit::moveDown(float distance)
        {
            glm::vec3 relativePosition = m_target - m_position;
            glm::vec3 direction = relativePosition;
            glm::vec3 right = glm::cross(direction, m_up);
            glm::vec3 up = glm::normalize(glm::cross(right, direction));

            float length = glm::length(direction);
            relativePosition = glm::normalize(relativePosition + distance * up) * length;

            m_position = m_target - relativePosition;

            m_up = up;

            m_needUpdateMatrix = true;
        }

        void Orbit::moveFront(float /*distance*/)
        {}

        void Orbit::moveBack(float /*distance*/)
        {}

        void Orbit::turnLeft(float /*angle*/)
        {}

        void Orbit::turnRight(float /*angle*/)
        {}

        void Orbit::turnUp(float /*angle*/)
        {}

        void Orbit::turnDown(float /*angle*/)
        {}

    }

    Camera::Camera(const projection::BasePtr projection, const view::BasePtr view)
        : m_projection(projection)
        , m_view(view)
    {}

    const projection::BasePtr Camera::projection() const
    {
        return m_projection;
    }

    const view::BasePtr Camera::view() const
    {
        return m_view;
    }

    void Camera::moveLeft(float distance)
    {
        m_view->moveLeft(distance);
    }

    void Camera::moveRight(float distance)
    {
        m_view->moveRight(distance);
    }

    void Camera::moveUp(float distance)
    {
        m_view->moveUp(distance);
    }

    void Camera::moveDown(float distance)
    {
        m_view->moveDown(distance);
    }

    void Camera::moveFront(float distance)
    {
        m_view->moveFront(distance);
    }

    void Camera::moveBack(float distance)
    {
        m_view->moveBack(distance);
    }

    void Camera::turnLeft(float angle)
    {
        m_view->turnLeft(angle);
    }

    void Camera::turnRight(float angle)
    {
        m_view->turnRight(angle);
    }

    void Camera::turnUp(float angle)
    {
        m_view->turnUp(angle);
    }

    void Camera::turnDown(float angle)
    {
        m_view->turnDown(angle);
    }

    void Camera::updateMatricies()
    {}

}
