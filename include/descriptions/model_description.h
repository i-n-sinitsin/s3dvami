// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <vector>

#include "descriptions/meshes_description.h"

namespace s3dvami
{
    struct ModelDescription
    {
        MeshesDescriptionPtr meshes;
    };

    using ModelDescriptionPtr = std::shared_ptr<ModelDescription>;
}
