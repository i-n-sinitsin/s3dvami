// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "descriptions/meshes.h"

namespace s3dvami::description
{
    struct Model
    {
        std::string name;

        MeshesPtr meshes;
    };

    using ModelPtr = std::shared_ptr<Model>;
}
