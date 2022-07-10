// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "shaders/shader.h"

#include "camera.h"

namespace s3dvami::objects
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
