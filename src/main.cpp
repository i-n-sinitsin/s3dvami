// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <iostream>
#include <optional>
#include <string>

#include "application.h"

using namespace std;

int main(int argc, const char **argv)
{
    std::optional<std::string> filename;
    if (argc == 2)
    {
        filename = std::string(argv[1]);
    }

    for (int i = 0; i < argc; i++)
        std::cout << std::string(argv[i]) << std::endl;

    s3dvami::Application *app = s3dvami::Application::GetInstance();
    app->init(filename);
    app->run();
    app->deinit();

    return 0;
}
