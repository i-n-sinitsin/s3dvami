// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "windows/menu_main.h"

#include "imgui.h"

namespace s3dvami::windows
{

    MainMenuBar::MainMenuBar(const MainMenuBarActions &actions)
        : m_mainMenuBarActions(actions)
    {}

    void MainMenuBar::draw()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open", "CTRL+O"))
                {
                    m_mainMenuBarActions.fileActions.openClick();
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "CTRL+Q"))
                {
                    m_mainMenuBarActions.fileActions.exitClick();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Checked", NULL, true))
                {
                }

                if (ImGui::MenuItem("Floor plate"))
                {
                    /// TODO: show about
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About"))
                {
                    m_mainMenuBarActions.helpActions.aboutClick();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

}
