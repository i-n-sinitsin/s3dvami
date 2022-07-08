// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>

namespace s3dvami::description
{
    struct Mesh
    {
        std::string id{};
        size_t verticiesAmount{0};
        size_t indeciesAmount{0};
    };

    using MeshPtr = std::shared_ptr<Mesh>;
}
