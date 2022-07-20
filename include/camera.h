// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>

#include "glm/glm.hpp"

namespace s3dvami
{
    class Camera
    {
    public:
        Camera();

        glm::mat4 getProjection() const;
        glm::mat4 getView() const;

        // 3D
        void setPerspectiveProjection(float fov, float width, float height, float near, float far);
        void setOrthoProjection(float left, float right, float bottom, float top, float near, float far);
        void setOrthoProjection(float width, float height, float depth);
        // 2D
        void setOrtho2DProjection(float left, float right, float bottom, float top);
        void setOrtho2DProjection(float width, float height);

        void setView(glm::vec3 eye, glm::vec3 pos, glm::vec3 up);

    private:
        glm::mat4 m_projection;
        glm::mat4 m_view;
    };

    using CameraPtr = std::shared_ptr<Camera>;
}
