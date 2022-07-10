// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "windows/wnd_model_description.h"

#include <algorithm>

#include "config.h"
#include "imgui.h"

namespace s3dvami::windows
{
    ModelDescription::ModelDescription()
        : m_descriptions{
            {"Nodes", false, Type::Attached,
                [=](description::ModelPtr model) {
                    drawNodesDescription(model->node);
                }},
            {"Meshes", false, Type::Attached,
                [=](description::ModelPtr model) {
                    drawMeshesDescription(model->meshes);
                }},

            {"Materials", false, Type::Attached,
                [=](description::ModelPtr /*model*/) {
                    drawMaterialsDescription();
                }},
            {"Textures", false, Type::Attached,
                [=](description::ModelPtr /*model*/) {
                    drawTexturesDescription();
                }},
        }
    {}

    void ModelDescription::draw(description::ModelPtr modelDescription)
    {
        // draw detached
        for (auto &it : m_descriptions)
        {
            if (it.type == Type::Detached)
            {
                auto open = true; //value.open;
                if (ImGui::Begin(it.name.c_str(), &open))
                {
                    it.draw(modelDescription);
                }
                ImGui::End();

                if (!open)
                {
                    it.type = Type::Attached;
                }
            }
        }

        // draw attached
        ImGuiIO &io = ImGui::GetIO();
        ImVec2 pos(0.0f, 20.0f);
        ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.0f, 0.0f));
        ImVec2 size(defaultModelDescroptionWidth, io.DisplaySize.y - 25.0f);
        ImGui::SetNextWindowSize(size);
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;

        if (ImGui::Begin("Scene Inspector", nullptr, flags))
        {
            if (!modelDescription->name.empty())
            {
                ImGui::Text("Model description:");
                ImGui::Text("Name -> %s", modelDescription->name.c_str());
            }

            for (auto &it : m_descriptions)
            {
                if (it.type == Type::Attached)
                {
                    //it.open = ImGui::CollapsingHeader(it.name.c_str(),  ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow  );
                    //ImVec2 size = ImGui::GetItemRectSize();
                    //ImGui::SameLine();
                    //ImGui::SetCursorPosX(size.x - size.y); // ArrowButton width = height = size.y
                    //if (ImGui::ArrowButton("Detach", ImGuiDir_::ImGuiDir_Up))
                    //{
                    //    it.type = Type::Detached;
                    //}

                    if ((it.open = ImGui::CollapsingHeader(it.name.c_str())))
                    {
                        if (ImGui::ArrowButton("Detach2", ImGuiDir_::ImGuiDir_Up))
                        {
                            it.type = Type::Detached;
                        }

                        it.draw(modelDescription);
                    }
                }
            }
        }
        ImGui::End();
    }

    void ModelDescription::drawMeshesDescription(description::MeshesPtr meshesDescription)
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

    void ModelDescription::drawMaterialsDescription()
    {}

    void ModelDescription::drawTexturesDescription()
    {}

    void ModelDescription::drawNodeDescription(description::NodePtr nodeDescription, int openAction)
    {
        if (openAction != -1)
            ImGui::SetNextItemOpen(openAction != 0);

        if (ImGui::TreeNode(nodeDescription->id.c_str()))
        {
            if (ImGui::BeginTable(nodeDescription->id.c_str(), 2))
            {
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
