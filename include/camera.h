// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>

#include "glm/glm.hpp"

namespace s3dvami
{
    namespace projection
    {
        enum Type
        {
            base,
            perspective,
            ortho,
            ortho2d
        };

        class Base
        {
        public:
            explicit Base(float width, float height, float near, float far);

            const glm::mat4 &matrix() const;
            Type type() const;

            void setWidth(float width);
            void setHeight(float height);
            void setNear(float near);
            void setFar(float far);

        protected:
            Type m_type;
            float m_width;
            float m_height;
            float m_near;
            float m_far;
            glm::mat4 m_projection;

            virtual void updateMatrix() = 0;
        };

        using BasePtr = std::shared_ptr<Base>;

        class Perspective : public Base
        {
        public:
            explicit Perspective(float fov, float width, float height, float near, float far);

            void setFov(float fov);

        private:
            float m_fov;

            void updateMatrix() override;
        };

        using PerspectivePtr = std::shared_ptr<Perspective>;

        class Ortho : public Base
        {
        public:
            explicit Ortho(float width, float height, float near, float far);

        private:
            void updateMatrix() override;
        };

        using OrthoPtr = std::shared_ptr<Ortho>;
    }

    class Camera
    {
    public:
        explicit Camera(const projection::BasePtr projection);

        const projection::BasePtr projection() const;
        glm::mat4 view() const;

        void setView(glm::vec3 eye, glm::vec3 pos, glm::vec3 up);

        void setPosition(const glm::vec3 &position);
        void setTarget(const glm::vec3 &position);
        void setUp(const glm::vec3 &position);







    private:
        projection::BasePtr m_projection;
        glm::mat4 m_view;

        glm::vec3 m_position;
        glm::vec3 m_target;
        glm::vec3 m_up;

        float m_scale;

        void updateMatricies();
    };

    using CameraPtr = std::shared_ptr<Camera>;
}
