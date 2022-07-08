// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "windows/wnd_model_description.h"

#include "config.h"
#include "imgui.h"

namespace s3dvami::windows
{

    ModelDescription::ModelDescription()
    {}

    void ModelDescription::draw(description::ModelPtr modelDescription)
    {
        ImGuiIO &io = ImGui::GetIO();
        ImVec2 pos(0.0f, 20.0f);
        ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.0f, 0.0f));
        ImVec2 size(defaultModelDescroptionWidth, io.DisplaySize.y - 25.0f);
        ImGui::SetNextWindowSize(size);
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;

        if (ImGui::Begin("Model Description", nullptr, flags))
        {
            ImGui::Text("Model description:");
            if (!modelDescription->name.empty())
            {
                ImGui::Text("Name -> %s", modelDescription->name.c_str());
            }

            drawMeshesDescription(modelDescription->meshes);
            drawMaterialsDescription();
            drawTexturesDescription();
            drawNodesDescription(modelDescription->node);

            ImGui::End();
        }
    }

    void ModelDescription::drawMeshesDescription(description::MeshesPtr meshesDescription)
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
                int openAction = -1;
                if (ImGui::Button("Open all"))
                {
                    openAction = 1;
                }
                ImGui::SameLine();
                if (ImGui::Button("Close all"))
                {
                    openAction = 0;
                }

                for (auto &meshDescription : meshesDescription->meshes)
                {
                    if (openAction != -1)
                        ImGui::SetNextItemOpen(openAction != 0);

                    if (ImGui::TreeNode(meshDescription->id.c_str()))
                    {
                        if (ImGui::BeginTable(meshDescription->id.c_str(), 2))
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

    void ModelDescription::drawMaterialsDescription()
    {
        if (ImGui::CollapsingHeader("Materials"))
        {
        }
    }

    void ModelDescription::drawTexturesDescription()
    {
        if (ImGui::CollapsingHeader("Textures"))
        {
        }
    }

    void ModelDescription::drawNodeDescription(description::NodePtr nodeDescription, int openAction)
    {
        if (openAction != -1)
            ImGui::SetNextItemOpen(openAction != 0);

        if (ImGui::TreeNode(nodeDescription->id.c_str()))
        {
            if (ImGui::BeginTable(nodeDescription->id.c_str(), 2))
            {
                /*
                ImGui::TableNextColumn();
                ImGui::Text("Verticies");
                ImGui::TableNextColumn();
                ImGui::Text("0");
                ImGui::TableNextRow();

                ImGui::TableNextColumn();
                ImGui::Text("Indicies");
                ImGui::TableNextColumn();
                ImGui::Text("0");
                ImGui::TableNextRow();
                */
                ImGui::EndTable();
            }

            for (auto &descr : nodeDescription->nodes)
            {
                drawNodeDescription(descr, openAction);
            }

            ImGui::TreePop();
        }
    }

    void ModelDescription::drawNodesDescription(description::NodePtr nodeDescription)
    {
        if (ImGui::CollapsingHeader("Nodes"))
        {
            if (nodeDescription)
            {
                int openAction = -1;
                if (ImGui::Button("Open all"))
                {
                    openAction = 1;
                }
                ImGui::SameLine();
                if (ImGui::Button("Close all"))
                {
                    openAction = 0;
                }

                drawNodeDescription(nodeDescription, openAction);
            }
        }
    }
}
