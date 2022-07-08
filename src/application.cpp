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

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    s3dvami::Application::GetInstance()->onKey(key, scancode, action, mods);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static void errorCallback(int /*error*/, const char *description)
{
    std::cerr << "Error:" << description << std::endl;
}

static void frameBufferSizeCallback(GLFWwindow * /*window*/, int width, int height)
{
    s3dvami::Application::GetInstance()->onResize(width, height);
}

namespace s3dvami
{
    Application::Application()
        : m_window(nullptr)
        , m_lastTime(0.0)
        , m_camera(new Camera())
        , m_model(nullptr)
        , m_floorPlate(nullptr)
        , m_chooseFileMessage(nullptr)
        , m_mainMenuBar(nullptr)
        , m_openFileDialog(nullptr)
        , m_modelDescription(nullptr)
    {}

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

        glfwSetKeyCallback(m_window, keyCallback);
        glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);

        initImGui();

        // model
        m_model = std::make_shared<Model>();

        reload(fileName);

        // init windows
        m_chooseFileMessage = std::make_shared<ChooseFileMessage>([=]() {
            m_openFileDialog->show();
        });
        m_mainMenuBar = std::make_shared<MainMenuBar>(
            [=]() {
                m_openFileDialog->show();
            },
            [=]() {
                glfwSetWindowShouldClose(m_window, GLFW_TRUE);
            });
        m_openFileDialog = std::make_shared<OpenFileDialog>([=](const std::string &fileName) {
            reload(fileName);
        });
        m_modelDescription = std::make_shared<ModelDescription>();

        // camera
        m_camera->setPerspectiveProjection(45.0f, defaultWindowWidth, defaultWindowHeight, defaultNearPlate, defaultFarPlate);

        float posX = defaultfloorPlateSize / 2.0f / 1.0f; // half / 2.0f
        float posY = defaultfloorPlateSize / 2.0f / 1.0f; // half / 3.0f
        float posZ = (defaultFarPlate - defaultNearPlate) / 2.0f;
        m_camera->setView(glm::vec3(posX, posY, posZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        // objects
        m_floorPlate = std::make_shared<FloorPlate>();
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

    void Application::onKey(int key, int /*scancode*/, int action, int /*mods*/)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_window, GLFW_TRUE);
        }
    }

    void Application::onResize(int width, int height)
    {
        glViewport(0, 0, width, height);
        m_camera->setPerspectiveProjection(45.0f, width, height, 0.1f, 100.0f);
        render();
    }

    void Application::process(float dt)
    {
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
        //glEnable(GL_DEPTH_TEST);
        //glDepthMask(GL_TRUE);
        //glDepthRange(0.0f, 1.0f);
        //glDepthFunc(GL_LESS);

        m_floorPlate->draw(m_camera);

        if (m_model)
        {
            m_model->draw(m_camera);
        }

        //glDisable(GL_DEPTH_TEST);

        // draw GUI
        renderImGui();
    }

    void Application::initImGui()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

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

        m_mainMenuBar->draw();

        if (m_model)
        {
            m_modelDescription->draw(m_model->getMeshesDesription());
        }

        if (m_model && !m_model->isLoaded())
        {
            m_chooseFileMessage->draw();
        }

        m_openFileDialog->draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Application::reload(const std::optional<std::string> &fileName)
    {
        if (fileName.has_value())
        {
            // load mode
            m_model.reset();
            m_model = std::make_shared<Model>();
            if (!m_model->load(fileName.value()))
            {
                ///TODO: show error message
                return;
            }
        }
    }
} // namespace s3dvami
