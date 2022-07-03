// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "windows/dlg_open_file.h"

#include <algorithm>
#include <filesystem>
#include <iostream>

#include "imgui.h"

namespace s3dvami
{

    OpenFileDialog::OpenFileDialog(std::function<void(const std::string &)> fileSelected)
        : m_fileSelected(fileSelected)
        , m_visible(false)
        , m_fsEntries{}
        , m_currentItem(1)
    {
        fillList();
    }

    void OpenFileDialog::draw()
    {
        if (!m_visible)
        {
            return;
        }

        ImGuiIO &io = ImGui::GetIO();
        ImVec2 pos(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
        ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
        if (ImGui::Begin("Select a file", nullptr, flags))
        {
            ImGui::Text("Select a file");

            // listbox
            char **items = new char *[m_fsEntries.size()];
            for (unsigned int i = 0; i < m_fsEntries.size(); i++)
            {
                items[i] = const_cast<char *>(m_fsEntries[i].c_str());
            }
            ImGui::ListBox("##hidelabel", &m_currentItem, items, m_fsEntries.size(), 10);
            delete[] items;

            // current path
            ImGui::Text("%s", std::string(std::filesystem::current_path()).c_str());

            ImGui::Separator();
            // buttons
            if (ImGui::Button("Choose"))
            {
                auto item = m_fsEntries[m_currentItem];
                if (item == "..")
                {
                    if (std::filesystem::current_path().has_parent_path())
                    {
                        std::filesystem::current_path(std::filesystem::current_path().parent_path());
                    }
                    fillList();
                    m_currentItem = 0;
                }
                else
                {
                    std::filesystem::path file = std::filesystem::current_path();
                    file.append(item);
                    if (std::filesystem::is_directory(file))
                    {
                        std::filesystem::current_path(file);
                        fillList();
                        m_currentItem = 0;
                    }
                    else
                    {
                        m_fileSelected(file);
                        m_visible = false;
                    }
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
            {
                m_visible = false;
            }

            ImGui::End();
        }
    }

    void OpenFileDialog::show()
    {
        m_visible = true;
        m_currentItem = 0;
    }

    void OpenFileDialog::fillList()
    {
        m_fsEntries.clear();
        std::filesystem::path path(std::filesystem::current_path());
        m_fsEntries.push_back("..");
        for (auto const &it : std::filesystem::directory_iterator{path})
        {
            m_fsEntries.push_back(std::filesystem::path(it).filename());
        }
        std::sort(m_fsEntries.begin(), m_fsEntries.end());
    }

}
