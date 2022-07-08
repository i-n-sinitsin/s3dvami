// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>

namespace s3dvami::description
{
    struct MeshDescription
    {
        std::string id{};
        size_t verticiesAmount{0};
        size_t indeciesAmount{0};
    };

    using MeshDescriptionPtr = std::shared_ptr<MeshDescription>;
}
