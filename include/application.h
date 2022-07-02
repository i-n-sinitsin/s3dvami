// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <GLFW/glfw3.h>

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

        void init();
        void run();
        void deinit();

        void onKey(int key, int scancode, int action, int mods);

    private:
        static Application *m_instance;
        GLFWwindow *m_window;

        double m_lastTime;

        void process(float dt);
        void render();

        void initImGui();
        void deinitGui();
        void renderImGui();
    };
} // namespace s3dvami
