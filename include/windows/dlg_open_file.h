// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>
#include <vector>

namespace s3dvami
{
    class OpenFileDialog
    {
    public:
        OpenFileDialog(std::function<void(const std::string &)> fileSelected);

        void draw();
        void show();

    private:
        std::function<void(const std::string &)> m_fileSelected;
        bool m_visible;
        std::vector<std::string> m_fsEntries;
        int m_currentItem;

        void fillList();
    };

    using OpenFileDialogPtr = std::shared_ptr<OpenFileDialog>;
}
