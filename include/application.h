// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <optional>

#include <GLFW/glfw3.h>

#include "model.h"

namespace s3dvami
{
    class Application
    {
    protected:
        Application();

    public:
        Application(Application &app) = delete;
        void operator=(const Application &) = delete;

        static Application *GetInstance();

        void init(const std::optional<std::string> &fileName);
        void run();
        void deinit();

        void onKey(int key, int scancode, int action, int mods);

    private:
        static Application *m_instance;
        GLFWwindow *m_window;

        double m_lastTime;

        ModelPtr m_model;

        void process(float dt);
        void render();

        void initImGui();
        void deinitGui();
        void renderImGui();

        void reload(const std::optional<std::string> &fileName);
    };
} // namespace s3dvami
