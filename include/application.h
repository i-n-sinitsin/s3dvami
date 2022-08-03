// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <array>
#include <optional>
#include <vector>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "model/model.h"

#include "windows/dlg_open_file.h"
#include "windows/menu_main.h"
#include "windows/msg_choose_file.h"
#include "windows/wnd_model_description.h"

#include "objects/axes.h"
#include "objects/floor_plate.h"

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

        void onError(const int error, const std::string &description);
        void onKey(const int key, const int scancode, const int action, const int mods);
        void onMouseMove(const glm::vec2 &pos);
        void onMouseScroll(const glm::vec2 &offset);
        void onMouseKey(const int key, const int action, const int mods);
        void onMouseEnter();
        void onMouseLeave();

        void onResize(const int width, const int height);
        void onDrop(const std::string &fileName);

    private:
        static Application *m_instance;
        GLFWwindow *m_window;

        bool m_showDemoMenu;

        // TODO: think about glfwGetKey
        enum KeyState
        {
            pressed,
            released
        };
        std::array<KeyState, GLFW_KEY_LAST> m_keysState;
        std::array<KeyState, GLFW_MOUSE_BUTTON_LAST> m_mouseKeysState;
        std::optional<glm::vec2> m_lastMousePosition;

        double m_lastTime;

        CameraPtr m_camera;
        model::ModelPtr m_model;

        //objects
        bool m_showFloorPlate;
        objects::FloorPlatePtr m_floorPlate;

        bool m_showGlobalAxes;
        objects::AxesPtr m_globalAxes;

        // windows
        windows::ChooseFileMessagePtr m_chooseFileMessage;
        windows::MainMenuPtr m_mainMenu;
        windows::OpenFileDialogPtr m_openFileDialog;
        windows::ModelPtr m_modelWindow;

        void process(float dt);
        void render();

        void initImGui();
        void deinitGui();
        void renderImGui();

        void processKeys(float dt);

        void reload(const std::optional<std::string> &fileName);
    };
} // namespace s3dvami
