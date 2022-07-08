// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>

#include "descriptions/model.h"

namespace s3dvami::windows
{
    class ModelDescription
    {
    public:
        explicit ModelDescription();

        void draw(description::ModelPtr modelDescription);

    private:
        void drawMeshesDescription(description::MeshesPtr meshesDescription);
        void drawMaterialsDescription();
        void drawTexturesDescription();
        void drawNodeDescription(description::NodePtr nodeDescription, int openAction);
        void drawNodesDescription(description::NodePtr nodeDescription);
    };

    using ModelDescriptionPtr = std::shared_ptr<ModelDescription>;
}
