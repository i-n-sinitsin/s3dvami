// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include "windows/dlg_open_file.h"

#include "imgui.h"

namespace s3dvami
{

    OpenFileDialog::OpenFileDialog()
        : m_visible(false)
    {}

    void OpenFileDialog::draw()
    {}

    void OpenFileDialog::show()
    {
        m_visible = true;
    }

}
