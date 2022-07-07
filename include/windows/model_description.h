// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>

namespace s3dvami
{
    class ModelDescription
    {
    public:
        explicit ModelDescription();

        void draw();

    private:

    };

    using ModelDescriptionPtr = std::shared_ptr<ModelDescription>;
}
