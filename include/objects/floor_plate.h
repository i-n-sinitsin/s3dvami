// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "glad/glad.h"

#include "camera.h"
#include "shaders/shader.h"
#include "vertex.h"

namespace s3dvami
{
    class FloorPlate
    {
    public:
        FloorPlate();
        ~FloorPlate();

        void draw(CameraPtr camera);

    private:
        GLuint m_VAO;
        GLuint m_VBO;
        GLuint m_EBO;

        ShaderPtr m_shader;
    };

    using FloorPlatePtr = std::shared_ptr<FloorPlate>;
}
