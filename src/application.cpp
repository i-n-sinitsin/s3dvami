// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "application.h"

#include <iostream>
#include <type_traits>

#include <GL/glu.h>
#include <math.h>

#include "config.h"

s3dvami::Application *s3dvami::Application::m_instance = nullptr;

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    s3dvami::Application::GetInstance()->onKey(key, scancode, action, mods);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static void errorCallback(int error, const char *description)
{
    std::cerr << "Error:" << description << std::endl;
}

namespace s3dvami
{
    Application::Application()
        : m_window(nullptr)
        , m_lastTime(0.0)
    {}

    Application *Application::GetInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new Application();
        }
        return m_instance;
    }

    void Application::init()
    {
        glfwSetErrorCallback(errorCallback);

        if (!glfwInit())
        {
            std::cout << "Can`t init glfw" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_window = glfwCreateWindow(defaultWindowWidth, defaultWindowHeight, "s3dvami", NULL, NULL);
        if (!m_window)
        {
            std::cout << "Can`t create window" << std::endl;
            return;
        }

        glfwMakeContextCurrent(m_window);

        glfwSetKeyCallback(m_window, keyCallback);
    }

    void Application::run()
    {
        if (!m_window)
        {
            return;
        }

        while (!glfwWindowShouldClose(m_window))
        {
            if (fabs(m_lastTime) < 0.00001)
            {
                m_lastTime = glfwGetTime();
                continue;
            }

            double time = glfwGetTime();
            double updateTime = time - m_lastTime;

            process(updateTime);
            render();

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

    void Application::deinit()
    {
        if (m_window)
        {
            glfwDestroyWindow(m_window);
        }
        glfwTerminate();
    }

    void Application::onKey(int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_window, GLFW_TRUE);
        }
    }

    void Application::process(float /*dt*/)
    {}

    void Application::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(defautBackgroundColor[0], defautBackgroundColor[1], defautBackgroundColor[2], defautBackgroundColor[3]);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthRange(0.0f, 1.0f);
        glDepthFunc(GL_LESS);

        glDisable(GL_DEPTH_TEST);
    }
} // namespace s3dvami
