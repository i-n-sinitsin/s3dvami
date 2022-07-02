// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>

namespace s3dvami
{
    class MainMenuBar
    {
    public:
        explicit MainMenuBar(std::function<void()> menuOpenClick, std::function<void()> menuExitClick);

        void draw();

    private:
        std::function<void()> m_menuOpenClick;
        std::function<void()> m_menuExitClick;
    };

    using MainMenuBarPtr = std::shared_ptr<MainMenuBar>;
}
