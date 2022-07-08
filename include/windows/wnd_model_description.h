// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>

#include "descriptions/model.h"

namespace s3dvami::windows
{
    class ModelDescriptionWindow
    {
    public:
        explicit ModelDescriptionWindow();

        void draw(description::ModelDescriptionPtr modelDescription);

    private:
        void drawMeshesDescription(description::MeshesDescriptionPtr meshesDescription);
        void drawMaterialsDescription();
        void drawTexturesDescription();
        void drawNodesDescription();
    };

    using ModelDescriptionWindowPtr = std::shared_ptr<ModelDescriptionWindow>;
}
