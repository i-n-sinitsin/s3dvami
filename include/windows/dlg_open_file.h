// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <memory>

namespace s3dvami
{
    class OpenFileDialog
    {
    public:
        OpenFileDialog();

        void draw();
        void show();

    private:
        bool m_visible;
    };

    using OpenFileDialogPtr = std::shared_ptr<OpenFileDialog>;
}
