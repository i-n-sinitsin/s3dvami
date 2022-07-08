// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "windows/menu_bar_main.h"

#include "imgui.h"

namespace s3dvami
{

    MainMenuBar::MainMenuBar(std::function<void()> menuOpenClick, std::function<void()> menuExitClick)
        : m_menuOpenClick(menuOpenClick)
        , m_menuExitClick(menuExitClick)
    {}

    void MainMenuBar::draw()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open", "CTRL+O"))
                {
                    m_menuOpenClick();
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "CTRL+Q"))
                {
                    m_menuExitClick();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About"))
                {
                    /// TODO: show about
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

}
