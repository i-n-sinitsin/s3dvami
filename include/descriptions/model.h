// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "descriptions/meshes.h"
#include "descriptions/node.h"

namespace s3dvami::description
{
    struct Model
    {
        std::string name{};

        MeshesPtr meshes{};
        NodePtr node{};
    };

    using ModelPtr = std::shared_ptr<Model>;
}
