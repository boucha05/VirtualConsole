#include "Application.h"

Application::Application()
{
    initialize();
}

Application::~Application()
{
    destroy();
}

void Application::initialize()
{
    mContext = nullptr;
}

bool Application::create()
{
    destroy();
    Console::Config config;
    mContext = Console::createContext(config);
    VERIFY(mContext);
    return true;
}

void Application::destroy()
{
    if (mContext)
        Console::destroyContext(*mContext);
    initialize();
}

bool Application::run()
{
    VERIFY(create());
    init();
    while (Console::isActive(*mContext))
    {
        update();
        render();
        flip();
    }
    return true;
}
