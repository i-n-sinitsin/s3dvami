// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "windows/wnd_model_description.h"

#include <algorithm>

#include "config.h"
#include "imgui.h"

namespace s3dvami::windows
{
    Model::Model()
        : m_pages{
            {"Nodes", false, Type::Attached,
                [=](model::ModelPtr model) {
                    drawNodesDescription(model->nodeMgr());
                }},
            {"Meshes", false, Type::Attached,
                [=](model::ModelPtr model) {
                    drawMeshesDescription(model->meshMgr());
                }},
            {"Materials", false, Type::Attached,
                [=](model::ModelPtr /*model*/) {
                    drawMaterialsDescription();
                }},
            {"Textures", false, Type::Attached,
                [=](model::ModelPtr model) {
                    drawTexturesDescription(model->textureMgr());
                }},
            {"Cameras", false, Type::Attached,
                [=](model::ModelPtr /*model*/) {
                    drawCamerasDescription();
                }},
            {"Animations", false, Type::Attached,
                [=](model::ModelPtr /*model*/) {
                    drawAnimationsDescription();
                }},
            {"Lights", false, Type::Attached,
                [=](model::ModelPtr /*model*/) {
                    drawLightsDescription();
                }},
        }
    {}

    void Model::draw(model::ModelPtr model)
    {
        // draw detached
        for (auto &it : m_pages)
        {
            if (it.type == Type::Detached)
            {
                auto open = true; //value.open;
                if (ImGui::Begin(it.name.c_str(), &open))
                {
                    it.draw(model);
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
            if (!model->name().empty())
            {
                ImGui::Text("Model description:");
                ImGui::Text("Name -> %s", model->name().c_str());
            }

            for (auto &it : m_pages)
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

                    if (ImGui::ArrowButton("Detach2", ImGuiDir_::ImGuiDir_Up))
                    {
                        it.type = Type::Detached;
                    }
                    ImGui::SameLine();

                    if ((it.open = ImGui::CollapsingHeader(it.name.c_str())))
                    {

                        it.draw(model);
                    }
                }
            }
        }
        ImGui::End();
    }

    void Model::drawMeshesDescription(model::MeshMgrPtr meshMgr)
    {
        // main info
        if (ImGui::BeginTable("table1", 3))
        {
            ImGui::TableNextColumn();
            ImGui::Text("Amount");
            ImGui::TableNextColumn();
            ImGui::Text("%u", meshMgr->meshAmount());
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("Verticies");
            ImGui::TableNextColumn();
            ImGui::Text("%u", meshMgr->verticiesAmount());
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("Indicies");
            ImGui::TableNextColumn();
            ImGui::Text("%u", meshMgr->indeciesAmount());
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

        for (auto &mesh : meshMgr->meshes())
        {
            if (openAction != -1)
                ImGui::SetNextItemOpen(openAction != 0);

            if (ImGui::TreeNode(mesh->id().c_str()))
            {
                if (ImGui::BeginTable(mesh->id().c_str(), 2))
                {
                    ImGui::TableNextColumn();
                    ImGui::Text("Verticies");
                    ImGui::TableNextColumn();
                    ImGui::Text("%u", mesh->verticiesAmount());
                    ImGui::TableNextRow();

                    ImGui::TableNextColumn();
                    ImGui::Text("Indicies");
                    ImGui::TableNextColumn();
                    ImGui::Text("%u", mesh->indicesAmount());
                    ImGui::TableNextRow();

                    ImGui::EndTable();
                }

                ImGui::TreePop();
            }
        }
    }

    void Model::drawMaterialsDescription()
    {}

    void Model::drawTexturesDescription(model::TextureMgrPtr textureMgr)
    {
        // main info
        if (ImGui::BeginTable("table1", 3))
        {
            ImGui::TableNextColumn();
            ImGui::Text("Amount");
            ImGui::TableNextColumn();
            ImGui::Text("%u", textureMgr->amount());
            ImGui::TableNextRow();

            ImGui::EndTable();
        }

        // textures
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
        for (auto &texture : textureMgr->textures())
        {
            if (openAction != -1)
                ImGui::SetNextItemOpen(openAction != 0);

            if (ImGui::TreeNode(texture->id().c_str()))
            {
                if (ImGui::BeginTable(texture->id().c_str(), 2))
                {
                    ImGui::TableNextColumn();
                    ImGui::Text("Size");
                    ImGui::TableNextColumn();
                    ImGui::Text("%u x %u", texture->width(), texture->height());
                    ImGui::TableNextRow();

                    ImGui::TableNextColumn();
                    ImGui::Text("Preview");
                    ImGui::TableNextColumn();
                    auto scale = 50.0f / std::max(texture->width(), texture->height());
                    ImVec2 size(texture->width() * scale, texture->height() * scale);
                    ImGui::Image(texture->glIdPtr(), size);

                    ImGui::TableNextRow();

                    ImGui::EndTable();
                }

                ImGui::TreePop();
            }
        }
    }

    void Model::drawNodeDescription(model::NodePtr node, int openAction)
    {
        if (openAction != -1)
            ImGui::SetNextItemOpen(openAction != 0);

        if (ImGui::TreeNode(node->id().c_str()))
        {
            if (ImGui::BeginTable(node->id().c_str(), 2))
            {
                ImGui::EndTable();
            }

            for (auto &it : node->nodes())
            {
                drawNodeDescription(it, openAction);
            }

            ImGui::TreePop();
        }
    }

    void Model::drawNodesDescription(model::NodeMgrPtr nodeMgr)
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

        if (ImGui::TreeNode(nodeMgr->id().c_str()))
        {
            if (ImGui::BeginTable(nodeMgr->id().c_str(), 2))
            {
                ImGui::EndTable();
            }

            for (auto &it : nodeMgr->nodes())
            {
                drawNodeDescription(it, openAction);
            }

            ImGui::TreePop();
        }
    }

    void Model::drawCamerasDescription()
    {}

    void Model::drawAnimationsDescription()
    {}

    void Model::drawLightsDescription()
    {}
}
