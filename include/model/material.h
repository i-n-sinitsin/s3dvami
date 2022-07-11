// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "assimp/scene.h"

#include "shaders/shader.h"

namespace s3dvami::model
{
    class Material
    {
    public:
        Material();

    private:
    };

    using MaterialPtr = std::shared_ptr<Material>;
}
