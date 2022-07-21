// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "application.h"

#include <iostream>
#include <type_traits>

#include <math.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "config.h"
#include "imgui.h"

s3dvami::Application *s3dvami::Application::m_instance = nullptr;

static void keyCallback(GLFWwindow * /*window*/, int key, int scancode, int action, int mods)
{
    s3dvami::Application::GetInstance()->onKey(key, scancode, action, mods);
}

static void errorCallback(int error, const char *description)
{
    s3dvami::Application::GetInstance()->onError(error, std::string(description));
}

static void frameBufferSizeCallback(GLFWwindow * /*window*/, int width, int height)
{
    s3dvami::Application::GetInstance()->onResize(width, height);
}

void mouseMoveCallback(GLFWwindow * /*window*/, double xPos, double yPos)
{
    s3dvami::Application::GetInstance()->onMouseMove(glm::vec2(xPos, yPos));
}

void mouseScrollCallback(GLFWwindow * /*window*/, double xOffset, double yOffset)
{
    s3dvami::Application::GetInstance()->onMouseScroll(glm::vec2(xOffset, yOffset));
}

static void mouseKeyCallback(GLFWwindow * /*window*/, int key, int action, int mods)
{
    s3dvami::Application::GetInstance()->onMouseKey(key, action, mods);
}

void dropCallback(GLFWwindow * /*window*/, int pathCount, const char *paths[])
{
    // take only first path if exist
    if (pathCount > 0)
    {
        s3dvami::Application::GetInstance()->onDrop(std::string(paths[0]));
    }
}

namespace s3dvami
{
    Application::Application()
        : m_window(nullptr)
        , m_keysState{}
        , m_mouseKeysState{}
        , m_lastMousePosition{}
        , m_lastTime(0.0)
        , m_camera(nullptr)
        , m_model(nullptr)
        , m_showFloorPlate(true)
        , m_floorPlate(nullptr)
        , m_showGlobalAxes(true)
        , m_globalAxes(nullptr)
        , m_chooseFileMessage(nullptr)
        , m_mainMenu(nullptr)
        , m_openFileDialog(nullptr)
        , m_modelWindow(nullptr)
    {
        m_keysState.fill(KeyState::released);
        m_mouseKeysState.fill(KeyState::released);
    }

    Application *Application::GetInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new Application();
        }
        return m_instance;
    }

    void Application::init(const std::optional<std::string> &fileName)
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
        glfwSwapInterval(1);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
            return;
        }

        // callbacks
        glfwSetKeyCallback(m_window, keyCallback);
        glfwSetCursorPosCallback(m_window, mouseMoveCallback);
        glfwSetScrollCallback(m_window, mouseScrollCallback);
        glfwSetMouseButtonCallback(m_window, mouseKeyCallback);
        glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);
        glfwSetDropCallback(m_window, dropCallback);
        //glfwSetInputMode

        initImGui();

        // model
        m_model = std::make_shared<model::Model>();

        reload(fileName);

        // init windows
        m_chooseFileMessage = std::make_shared<windows::ChooseFileMessage>([=]() {
            m_openFileDialog->show();
        });

        windows::MainMenuActions mainMenuBarActions;
        mainMenuBarActions.fileActions.openClick = [=]() {
            m_openFileDialog->show();
        };
        mainMenuBarActions.fileActions.exitClick = [=]() {
            glfwSetWindowShouldClose(m_window, GLFW_TRUE);
        };

        mainMenuBarActions.viewActions.isFloorShow = m_showFloorPlate;
        mainMenuBarActions.viewActions.floorClick = [=]() {
            m_showFloorPlate = !m_showFloorPlate;
        };

        mainMenuBarActions.viewActions.isGlobalAxes = m_showGlobalAxes;
        mainMenuBarActions.viewActions.globalAxesClick = [=]() {
            m_showGlobalAxes = !m_showGlobalAxes;
        };

        m_mainMenu = std::make_shared<windows::MainMenu>(mainMenuBarActions);

        m_openFileDialog = std::make_shared<windows::OpenFileDialog>([=](const std::string &fileName) {
            reload(fileName);
        });
        m_modelWindow = std::make_shared<windows::Model>();

        // camera
        m_camera = std::make_shared<Camera>(std::make_shared<projection::Perspective>(45.0f, defaultWindowWidth, defaultWindowHeight, defaultNearPlate, defaultFarPlate), std::make_shared<view::Free>());
        m_camera->view()->setPosition({25.0f, 25.0f, 50.0f});
        m_camera->view()->setTarget({0.0f, 0.0f, 0.0f});

        // objects
        m_floorPlate = std::make_shared<objects::FloorPlate>();
        m_globalAxes = std::make_shared<objects::Axes>(defaultGlobalAxesLength, defaultGlobalAxesWidth);
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
            deinitGui();
            glfwDestroyWindow(m_window);
        }
        glfwTerminate();
    }

    void Application::onError(const int error, const std::string &description)
    {
        std::cout << "Error: ( " << error << " ) Description: " << description << std::endl;
    }

    void Application::onKey(int key, const int /*scancode*/, const int action, const int mods)
    {
        [[maybe_unused]] auto isShiftPressed = mods & GLFW_MOD_SHIFT;
        [[maybe_unused]] auto isCtrlPressed = mods & GLFW_MOD_CONTROL;
        [[maybe_unused]] auto isAltPressed = mods & GLFW_MOD_ALT;
        [[maybe_unused]] auto isSuperPressed = mods & GLFW_MOD_SUPER;
        [[maybe_unused]] auto isCapsLockPressed = mods & GLFW_MOD_CAPS_LOCK;
        [[maybe_unused]] auto isNumLockPressed = mods & GLFW_MOD_NUM_LOCK;

        // process key state
        // need store key state for work with long press status
        if (static_cast<unsigned int>(key) < m_keysState.size())
        {
            if (action == GLFW_PRESS || action == GLFW_REPEAT)
            {
                m_keysState[key] = KeyState::pressed;
            }
            else if (action == GLFW_RELEASE)
            {
                m_keysState[key] = KeyState::released;
            }
        }

        // check single press/release
        auto close = (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS);
        if (close)
        {
            glfwSetWindowShouldClose(m_window, GLFW_TRUE);
        }

        auto openFile = (key == GLFW_KEY_O && action == GLFW_PRESS && isCtrlPressed);
        if (openFile)
        {
            m_openFileDialog->show();
        }
    }

    void Application::onMouseMove(const glm::vec2 &pos)
    {
        if (m_lastMousePosition.has_value())
        {
        }
        else
        {
            m_lastMousePosition = pos;
        }
    }

    void Application::onMouseScroll(const glm::vec2 & /*offset*/)
    {}

    void Application::onMouseKey(const int key, const int action, const int mods)
    {
        [[maybe_unused]] auto isShiftPressed = mods & GLFW_MOD_SHIFT;
        [[maybe_unused]] auto isCtrlPressed = mods & GLFW_MOD_CONTROL;
        [[maybe_unused]] auto isAltPressed = mods & GLFW_MOD_ALT;
        [[maybe_unused]] auto isSuperPressed = mods & GLFW_MOD_SUPER;
        [[maybe_unused]] auto isCapsLockPressed = mods & GLFW_MOD_CAPS_LOCK;
        [[maybe_unused]] auto isNumLockPressed = mods & GLFW_MOD_NUM_LOCK;

        // process key state
        // need store key state for work with long press status
        if (static_cast<unsigned int>(key) < m_mouseKeysState.size())
        {
            if (action == GLFW_PRESS || action == GLFW_REPEAT)
            {
                m_mouseKeysState[key] = KeyState::pressed;
            }
            else if (action == GLFW_RELEASE)
            {
                m_mouseKeysState[key] = KeyState::released;
            }
        }

        //GLFW_MOUSE_BUTTON_LEFT
        //GLFW_MOUSE_BUTTON_RIGHT
        //GLFW_MOUSE_BUTTON_MIDDLE
    }

    void Application::onResize(const int width, const int height)
    {
        glViewport(0, 0, width, height);
        m_camera->projection()->setWidth(width);
        m_camera->projection()->setHeight(height);
        render();
    }

    void Application::onDrop(const std::string &fileName)
    {
        reload(fileName);
    }

    void Application::process(float dt)
    {
        processKeys(dt);
        if (m_model)
        {
            m_model->process(dt);
        }
    }

    void Application::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(defautBackgroundColor[0], defautBackgroundColor[1], defautBackgroundColor[2], defautBackgroundColor[3]);

        // draw scene
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_TEXTURE_2D);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthRange(0.0f, 1.0f);
        glDepthFunc(GL_LESS);

        if (m_model)
        {
            m_model->draw(m_camera);
        }

        if (m_showFloorPlate)
        {
            m_floorPlate->draw(m_camera);
        }

        if (m_showGlobalAxes)
        {
            m_globalAxes->draw(m_camera);
        }

        glDisable(GL_DEPTH_TEST);

        glDisable(GL_TEXTURE_2D);

        //glDisable(GL_BLEND);

        // draw GUI
        renderImGui();
    }

    void Application::initImGui()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        // disable save ini file
        io.IniFilename = nullptr;

        ///TODO: switch style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        io.Fonts->AddFontDefault();
    }

    void Application::deinitGui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Application::renderImGui()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        m_mainMenu->draw();

        if (m_model && m_model->isLoaded())
        {
            m_modelWindow->draw(m_model);
        }

        if (m_model && !m_model->isLoaded())
        {
            m_chooseFileMessage->draw();
        }

        m_openFileDialog->draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Application::processKeys(float dt)
    {
        auto leftPressed = (m_keysState[GLFW_KEY_LEFT] == KeyState::pressed || m_keysState[GLFW_KEY_A] == KeyState::pressed);
        if (leftPressed)
        {
            m_camera->moveLeft(0.05f * dt);
        }

        auto rightPressed = (m_keysState[GLFW_KEY_RIGHT] == KeyState::pressed || m_keysState[GLFW_KEY_D] == KeyState::pressed);
        if (rightPressed)
        {
            m_camera->moveRight(0.05f * dt);
        }

        auto upPressed = (m_keysState[GLFW_KEY_UP] == KeyState::pressed || m_keysState[GLFW_KEY_W] == KeyState::pressed);
        if (upPressed)
        {
            m_camera->moveFront(0.05f * dt);
        }

        auto downPressed = (m_keysState[GLFW_KEY_DOWN] == KeyState::pressed || m_keysState[GLFW_KEY_S] == KeyState::pressed);
        if (downPressed)
        {
            m_camera->moveBack(0.05f * dt);
        }

        auto ctrlUpPressed = (m_keysState[GLFW_KEY_E] == KeyState::pressed || (m_keysState[GLFW_KEY_RIGHT_CONTROL] == KeyState::pressed && m_keysState[GLFW_KEY_UP] == KeyState::pressed));
        if (ctrlUpPressed)
        {
            m_camera->moveUp(0.05f * dt);
        }

        auto ctrlDownPressed = (m_keysState[GLFW_KEY_Q] == KeyState::pressed || (m_keysState[GLFW_KEY_RIGHT_CONTROL] == KeyState::pressed && m_keysState[GLFW_KEY_DOWN] == KeyState::pressed));
        if (ctrlDownPressed)
        {
            m_camera->moveDown(0.05f * dt);
        }
    }

    void Application::reload(const std::optional<std::string> &fileName)
    {
        if (fileName.has_value())
        {
            // load mode
            m_model.reset();
            m_model = std::make_shared<model::Model>();
            if (!m_model->load(fileName.value()))
            {
                ///TODO: show error message
                return;
            }

            //std::optional<AABB> nodeAABB = m_model->nodeMgr()->aabb();
            //glm::vec3 eye = nodeAABB.value().center();
            //m_camera->setView(eye + glm::vec3(25.0f, 25.0f, 50.0f), eye, glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }
} // namespace s3dvami
