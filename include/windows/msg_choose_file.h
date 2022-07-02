// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <functional>
#include <memory>

namespace s3dvami
{
    class ChooseFileMessage
    {
    public:
        explicit ChooseFileMessage(std::function<void()> buttonClick);

        void draw();

    private:
        std::function<void()> m_buttonClick;
    };

    using ChooseFileMessagePtr = std::shared_ptr<ChooseFileMessage>;
}
