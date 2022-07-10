// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "model/model.h"

namespace s3dvami::windows
{
    class Model
    {
    public:
        Model();

        void draw(model::ModelPtr modelDescription);

    private:
        enum class Type
        {
            Attached,
            Detached
        };

        struct Page
        {
            std::string name;
            bool open;
            Type type;
            std::function<void(model::ModelPtr)> draw;
        };

        std::vector<Page> m_pages;

        void drawMeshesDescription(model::MeshMgrPtr meshMgr);
        void drawMaterialsDescription();
        void drawTexturesDescription();
        void drawNodeDescription(model::NodePtr node, int openAction);
        void drawNodesDescription(model::NodeMgrPtr nodeMgr);
        void drawCamerasDescription();
        void drawAnimationsDescription();
        void drawLightsDescription();
    };

    using ModelPtr = std::shared_ptr<Model>;
}
