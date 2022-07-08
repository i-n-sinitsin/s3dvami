// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>

namespace s3dvami::description
{
    struct Node;

    using NodePtr = std::shared_ptr<Node>;

    struct Node
    {
        std::string id{};
        std::vector<unsigned int> meshes;
        std::vector<NodePtr> nodes{};
    };
}
