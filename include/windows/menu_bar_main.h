// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>

namespace s3dvami
{
    struct MainMenuBarActions
    {
        struct
        {
            std::function<void()> openClick;
            std::function<void()> exitClick;
        } fileActions;

        struct
        {
            std::function<void()> floorClick;
        } viewActions;

        struct
        {
            std::function<void()> aboutClick;
        } helpActions;
    };

    class MainMenuBar
    {
    public:
        explicit MainMenuBar(const MainMenuBarActions &actions);

        void draw();

    private:
        MainMenuBarActions m_mainMenuBarActions;
    };

    using MainMenuBarPtr = std::shared_ptr<MainMenuBar>;
}
