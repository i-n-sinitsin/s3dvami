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
            ortho2d,
        };

        class Base
        {
        public:
            explicit Base(float width, float height, float near, float far);

            const glm::mat4 &matrix();
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
            bool m_needUpdateMatrix;

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

    namespace view
    {
        enum class Type
        {
            base,
            free,
            orbit,
        };

        class Base;
        using BasePtr = std::shared_ptr<Base>;

        class Base
        {
        public:
            explicit Base(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &up);
            Base(const BasePtr &view);
            Type type() const;

            const glm::mat4 &matrix();

            void setPosition(const glm::vec3 &position);
            void setTarget(const glm::vec3 &target);
            void setUp(const glm::vec3 &up);

            glm::vec3 position() const;
            glm::vec3 target() const;
            glm::vec3 up() const;

            virtual void moveLeft(float distance) = 0;
            virtual void moveRight(float distance) = 0;
            virtual void moveUp(float distance) = 0;
            virtual void moveDown(float distance) = 0;
            virtual void moveFront(float distance) = 0;
            virtual void moveBack(float distance) = 0;

            virtual void turnLeft(float distance) = 0;
            virtual void turnRight(float distance) = 0;
            virtual void turnUp(float distance) = 0;
            virtual void turnDown(float distance) = 0;

        protected:
            Type m_type;
            bool m_needUpdateMatrix;
            glm::mat4 m_view;

            glm::vec3 m_position;
            glm::vec3 m_target;
            glm::vec3 m_up;

            void updateMatrix();
        };

        class Free : public Base
        {
        public:
            explicit Free(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &up);
            Free(const BasePtr &view);

            void moveLeft(float distance) override;
            void moveRight(float distance) override;
            void moveUp(float distance) override;
            void moveDown(float distance) override;
            void moveFront(float distance) override;
            void moveBack(float distance) override;

            void turnLeft(float distance) override;
            void turnRight(float distance) override;
            void turnUp(float distance) override;
            void turnDown(float distance) override;
        };

        using FreePtr = std::shared_ptr<Free>;

        class Orbit : public Base
        {
        public:
            explicit Orbit(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &up);
            Orbit(const BasePtr &view);

            void moveLeft(float distance) override;
            void moveRight(float distance) override;
            void moveUp(float distance) override;
            void moveDown(float distance) override;
            void moveFront(float distance) override;
            void moveBack(float distance) override;

            void turnLeft(float distance) override;
            void turnRight(float distance) override;
            void turnUp(float distance) override;
            void turnDown(float distance) override;
        };

        using OrbitPtr = std::shared_ptr<Orbit>;
    }

    class Camera
    {
    public:
        explicit Camera(const projection::BasePtr projection, const view::BasePtr view);

        const projection::BasePtr projection() const;
        const view::BasePtr view() const;

        void moveLeft(float distance);
        void moveRight(float distance);
        void moveUp(float distance);
        void moveDown(float distance);
        void moveFront(float distance);
        void moveBack(float distance);

        void turnLeft(float angle);
        void turnRight(float angle);
        void turnUp(float angle);
        void turnDown(float angle);

        void changeViewTo(view::Type type);
        void changeViewTo(const view::BasePtr view);

    private:
        projection::BasePtr m_projection;
        view::BasePtr m_view;

        void updateMatricies();
    };

    using CameraPtr = std::shared_ptr<Camera>;
}
