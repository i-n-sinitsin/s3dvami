// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "windows/msg_choose_file.h"

#include "config.h"
#include "imgui.h"

namespace s3dvami::windows
{

    ChooseFileMessage::ChooseFileMessage(std::function<void()> buttonClick)
        : m_buttonClick(buttonClick)
    {}

    void ChooseFileMessage::draw()
    {
        ImGuiIO &io = ImGui::GetIO();
        ImVec2 pos(defaultModelDescroptionWidth + (io.DisplaySize.x - defaultModelDescroptionWidth) * 0.5f, io.DisplaySize.y * 0.5f);
        ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
        if (ImGui::Begin("Message", nullptr, flags))
        {
            ImGui::Text("   Drop file to view  ");
            ImGui::Text("           or         ");

            if (ImGui::Button("    Choose a file    "))
            {
                m_buttonClick();
            }
        }
        ImGui::End();
    }

}
