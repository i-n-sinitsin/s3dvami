// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "windows/model_description.h"

#include "imgui.h"
#include "config.h"

namespace s3dvami
{

    ModelDescription::ModelDescription()
    {}

    void ModelDescription::draw()
    {
        ImGuiIO &io = ImGui::GetIO();
        ImVec2 pos(0.0f, 20.0f);
        ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.0f, 0.0f));
        ImVec2 size(defaultModelDescroptionWidth, io.DisplaySize.y);
        ImGui::SetNextWindowSize(size);
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;

        if (ImGui::Begin("Model Description", nullptr, flags)){

            ImGui::Text("Model description:");

            if (ImGui::CollapsingHeader("Meshes"))
            {

            }

            ImGui::End();
        }
    }

}
