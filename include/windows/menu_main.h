// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>

namespace s3dvami::windows
{
    struct MainMenuActions
    {
        struct
        {
            std::function<void()> openClick;
            std::function<void()> exitClick;
        } fileActions;

        struct
        {
            bool isFloorShow;
            std::function<void()> floorClick;
        } viewActions;

        struct
        {
            std::function<void()> aboutClick;
        } helpActions;
    };

    class MainMenu
    {
    public:
        explicit MainMenu(const MainMenuActions &actions);

        void draw();

    private:
        MainMenuActions m_mainMenuActions;
    };

    using MainMenuPtr = std::shared_ptr<MainMenu>;
}
