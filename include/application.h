// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <optional>
#include <vector>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "windows/dlg_open_file.h"
#include "windows/menu_main.h"
#include "windows/msg_choose_file.h"
#include "windows/wnd_model_description.h"

#include "model.h"
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

        void onKey(int key, int scancode, int action, int mods);
        void onResize(int width, int height);

    private:
        static Application *m_instance;
        GLFWwindow *m_window;

        double m_lastTime;

        CameraPtr m_camera;
        ModelPtr m_model;

        //objects
        bool m_showFloorPlate;
        objects::FloorPlatePtr m_floorPlate;

        // windows
        windows::ChooseFileMessagePtr m_chooseFileMessage;
        windows::MainMenuPtr m_mainMenu;
        windows::OpenFileDialogPtr m_openFileDialog;
        windows::ModelDescriptionPtr m_modelDescriptionWindow;

        void process(float dt);
        void render();

        void initImGui();
        void deinitGui();
        void renderImGui();

        void reload(const std::optional<std::string> &fileName);
    };
} // namespace s3dvami
