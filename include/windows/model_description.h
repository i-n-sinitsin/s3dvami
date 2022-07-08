// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>

#include "descriptions/model_description.h"

namespace s3dvami
{
    class ModelDescriptionWindow
    {
    public:
        explicit ModelDescriptionWindow();

        void draw(ModelDescriptionPtr modelDescription);

    private:
        void drawMeshesDescription(MeshesDescriptionPtr meshesDescription);
        void drawMaterialsDescription();
        void drawTexturesDescription();
        void drawNodesDescription();
    };

    using ModelDescriptionWindowPtr = std::shared_ptr<ModelDescriptionWindow>;
}
