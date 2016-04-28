#pragma once

namespace Console
{
    struct Context;
}

class LuaState
{
public:
    virtual bool openConsole(Console::Context& context) = 0;

    static LuaState* create();
    static void destroy(LuaState& instance);
};
