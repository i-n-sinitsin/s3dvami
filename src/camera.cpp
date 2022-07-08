// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace s3dvami
{
    Camera::Camera()
        : m_projection(1.0f)
        , m_view(1.0f)
    {}

    glm::mat4 Camera::getProjection() const
    {
        return m_projection;
    }

    glm::mat4 Camera::getView() const
    {
        return m_view;
    }

    void Camera::setPerspectiveProjection(float fov, float width, float height, float near, float far)
    {
        m_projection = glm::perspective(glm::radians(fov), width / height, near, far);
    }

    void Camera::setView(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
    {
        m_view = glm::lookAt(eye, center, up);
    }
}
