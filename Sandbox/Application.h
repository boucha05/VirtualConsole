#pragma once

#include "Console.h"
#include "LuaState.h"
#include <memory>

#define VERIFY(expr)    if(expr) ; else return false

class Application
{
public:
    Application();
    virtual ~Application();
    bool create();
    void destroy();
    bool run();

    Console::Context& context()
    {
        return *mContext;
    }

    Lua::State& lua()
    {
        return mLua;
    }

protected:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

private:
    void initialize();

    std::unique_ptr<Console::Context>   mContext;
    Lua::State                          mLua;
};
