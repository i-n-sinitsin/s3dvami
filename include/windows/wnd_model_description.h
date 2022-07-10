// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "descriptions/model.h"

namespace s3dvami::windows
{
    class ModelDescription
    {
    public:
        ModelDescription();

        void draw(description::ModelPtr modelDescription);

    private:
        enum class Type
        {
            Attached,
            Detached
        };

        struct Description
        {
            std::string name;
            bool open;
            Type type;
            std::function<void(description::ModelPtr)> draw;
        };

        std::vector<Description> m_descriptions;

        void drawMeshesDescription(description::MeshesPtr meshesDescription);

        void drawMaterialsDescription();

        void drawTexturesDescription();

        void drawNodeDescription(description::NodePtr nodeDescription, int openAction);
        void drawNodesDescription(description::NodePtr nodeDescription);
    };

    using ModelDescriptionPtr = std::shared_ptr<ModelDescription>;
}
