// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <memory>
#include <string>

namespace s3dvami
{
    class Model
    {
    public:
        Model();
        ~Model();

        bool load(const std::string &fileName);
        void draw();
        void process(float dt);

        bool isLoaded()
        {
            return m_loaded;
        }

    private:
        bool m_loaded;

        bool loadTextures();
        bool loadMaterials();
        bool loadMeshes();
        bool loadNodes();
        bool loadAnimations();
    };

    using ModelPtr = std::shared_ptr<Model>;

}
