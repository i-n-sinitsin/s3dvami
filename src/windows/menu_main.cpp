// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "windows/menu_main.h"

#include "imgui.h"

namespace s3dvami::windows
{

    MainMenu::MainMenu(const MainMenuActions &actions)
        : m_mainMenuActions(actions)
    {}

    void MainMenu::draw()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open", "CTRL+O"))
                {
                    m_mainMenuActions.fileActions.openClick();
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "ESC"))
                {
                    m_mainMenuActions.fileActions.exitClick();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Floor Plane", NULL, &(m_mainMenuActions.viewActions.isFloorShow)))
                {
                    m_mainMenuActions.viewActions.floorClick();
                }

                if (ImGui::MenuItem("Global Axes", NULL, &(m_mainMenuActions.viewActions.isGlobalAxes)))
                {
                    m_mainMenuActions.viewActions.globalAxesClick();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About"))
                {
                    m_mainMenuActions.helpActions.aboutClick();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

}
