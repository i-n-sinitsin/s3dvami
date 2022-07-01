// Copyright © 2022 Sinitsin Ivan, Contacts: <i.n.sinitsin@gmail.com>

#pragma once

#include <GLFW/glfw3.h>

class Application
{
protected:
    Application();
public:
    Application( Application& app ) = delete;
    void operator=( const Application& ) = delete;
    
    static Application* GetInstance();
    
    void init();
    void run();
    void deinit();

    void onKey( int key, int scancode, int action, int mods );
    
private:
    
    static Application* m_instance;
    GLFWwindow* m_window;
    
    double m_lastTime;
};


