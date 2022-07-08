// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "descriptions/mesh.h"

namespace s3dvami::description
{
    struct MeshesDescription
    {
        size_t amount{0};
        size_t verticiesAmount{0};
        size_t indeciesAmount{0};
        std::vector<MeshDescriptionPtr> meshes{};
    };

    using MeshesDescriptionPtr = std::shared_ptr<MeshesDescription>;
}
