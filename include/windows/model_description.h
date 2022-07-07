// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>

#include "descriptions/meshes_description.h"

namespace s3dvami
{
    class ModelDescription
    {
    public:
        explicit ModelDescription();

        void draw(MeshesDescriptionPtr meshesDescription);

    private:
        void drawMeshesDescription(MeshesDescriptionPtr meshesDescription);
    };

    using ModelDescriptionPtr = std::shared_ptr<ModelDescription>;
}
