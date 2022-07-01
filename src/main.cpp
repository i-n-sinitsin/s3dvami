// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#include <iostream>
#include <string>

#include "application.h"

using namespace std;

int main(int argc, const char **argv)
{
    // for(int i = 0; i < argc; i++){
    //    std::string tmp(argv[i]);
    //    std::cout << i << "  " << tmp << std::endl;
    //}

    s3dvami::Application *app = s3dvami::Application::GetInstance();
    app->init();
    app->run();
    app->deinit();

    return 0;
}
