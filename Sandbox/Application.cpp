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
    mLua = nullptr;
}

bool Application::create()
{
    destroy();
    Console::Config config;
    mContext = Console::createContext(config);
    VERIFY(mContext);
    mLua = LuaState::create();
    VERIFY(mLua);
    VERIFY(mLua->openConsole(*mContext));
    return true;
}

void Application::destroy()
{
    if (mLua)
        LuaState::destroy(*mLua);
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
