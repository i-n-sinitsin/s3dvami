// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "windows/model_description.h"

#include "config.h"
#include "imgui.h"

namespace s3dvami
{

    ModelDescription::ModelDescription()
    {}

    void ModelDescription::draw(MeshesDescriptionPtr meshesDescription)
    {
        ImGuiIO &io = ImGui::GetIO();
        ImVec2 pos(0.0f, 20.0f);
        ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.0f, 0.0f));
        ImVec2 size(defaultModelDescroptionWidth, io.DisplaySize.y);
        ImGui::SetNextWindowSize(size);
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;

        if (ImGui::Begin("Model Description", nullptr, flags))
        {

            ImGui::Text("Model description:");

            drawMeshesDescription(meshesDescription);

            ImGui::End();
        }
    }

    void ModelDescription::drawMeshesDescription(MeshesDescriptionPtr meshesDescription)
    {
        if (ImGui::CollapsingHeader("Meshes"))
        {
            if (meshesDescription)
            {
                // main info
                if (ImGui::BeginTable("table1", 3))
                {
                    ImGui::TableNextColumn();
                    ImGui::Text("Amount");
                    ImGui::TableNextColumn();
                    ImGui::Text("%zu", meshesDescription->amount);
                    ImGui::TableNextRow();

                    ImGui::TableNextColumn();
                    ImGui::Text("Verticies");
                    ImGui::TableNextColumn();
                    ImGui::Text("%zu", meshesDescription->verticiesAmount);
                    ImGui::TableNextRow();

                    ImGui::TableNextColumn();
                    ImGui::Text("Indicies");
                    ImGui::TableNextColumn();
                    ImGui::Text("%zu", meshesDescription->indeciesAmount);
                    ImGui::TableNextRow();

                    ImGui::EndTable();
                }

                // meshes
                int open_action = -1;
                ImGui::SameLine();
                if (ImGui::Button("Open all"))
                    open_action = 1;
                ImGui::SameLine();
                if (ImGui::Button("Close all"))
                    open_action = 0;

                for (auto meshDescription : meshesDescription->meshes)
                {
                    if (open_action != -1)
                        ImGui::SetNextItemOpen(open_action != 0);

                    if (ImGui::TreeNode(meshDescription->id.c_str()))
                    {
                        if (ImGui::BeginTable(meshDescription->id.c_str(), 3))
                        {
                            ImGui::TableNextColumn();
                            ImGui::Text("Verticies");
                            ImGui::TableNextColumn();
                            ImGui::Text("%zu", meshDescription->verticiesAmount);
                            ImGui::TableNextRow();

                            ImGui::TableNextColumn();
                            ImGui::Text("Indicies");
                            ImGui::TableNextColumn();
                            ImGui::Text("%zu", meshDescription->indeciesAmount);
                            ImGui::TableNextRow();

                            ImGui::EndTable();
                        }

                        ImGui::TreePop();
                    }
                }
            }
        }
    }
}
