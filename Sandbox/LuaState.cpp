#include "LuaState.h"
#include "Console.h"

extern "C" {
#include <Contrib/lua-5.2.4/src/lauxlib.h>
#include <Contrib/lua-5.2.4/src/lstate.h>
#include <Contrib/lua-5.2.4/src/lualib.h>
}

namespace
{
    bool check_stack_size(lua_State* state, int size)
    {
        return lua_gettop(state) == size;
    }

    bool check_stack_range(lua_State* state, int min_size, int max_size)
    {
        int top = lua_gettop(state);
        return (top >= min_size) && (top <= max_size);
    }

    bool read(lua_State* state, int index, bool& value)
    {
        value = lua_toboolean(state, index) != 0;
        return true;
    }

    bool read(lua_State* state, int index, int& value)
    {
        if (!lua_isnumber(state, index))
            return false;
        value = static_cast<int>(lua_tonumber(state, index));
        return true;
    }

    bool read(lua_State* state, int index, float& value)
    {
        if (!lua_isnumber(state, index))
            return false;
        value = static_cast<float>(lua_tonumber(state, index));
        return true;
    }

    bool read(lua_State* state, int index, const void*& value)
    {
        if (!lua_isuserdata(state, index))
            return false;
        value = lua_touserdata(state, index);
        return true;
    }

    bool read(lua_State* state, int index, const char*& value)
    {
        if (!lua_isstring(state, index))
            return false;
        value = lua_tostring(state, index);
        return true;
    }

    template <typename T>
    bool read_opt(lua_State* state, int index, T& value)
    {
        int top = lua_gettop(state);
        if (top < index)
            return true;
        return read(state, index, value);
    }

    void push(lua_State* state, int value)
    {
        lua_pushinteger(state, value);
    }

    void push(lua_State* state, void* value)
    {
        if (value)
            lua_pushlightuserdata(state, value);
        else
            lua_pushnil(state);
    }
}

namespace Console
{
    static const char* cContext = "Context";

    void set_context(lua_State* state, Console::Context& context)
    {
        lua_pushlightuserdata(state, const_cast<char*>(cContext));
        lua_pushlightuserdata(state, &context);
        lua_settable(state, LUA_REGISTRYINDEX);
    }

    Console::Context& get_context(lua_State* state)
    {
        lua_pushlightuserdata(state, const_cast<char*>(cContext));
        lua_gettable(state, LUA_REGISTRYINDEX);
        return *static_cast<Console::Context*>(lua_touserdata(state, -1));
    }

#include "LuaConsoleBindings.h"
}

namespace Content
{
    static const char* cContext = "Content";

    void set_context(lua_State* state, Console::Context& context)
    {
        lua_pushlightuserdata(state, const_cast<char*>(cContext));
        lua_pushlightuserdata(state, &context);
        lua_settable(state, LUA_REGISTRYINDEX);
    }

    Console::Context& get_context(lua_State* state)
    {
        lua_pushlightuserdata(state, const_cast<char*>(cContext));
        lua_gettable(state, LUA_REGISTRYINDEX);
        return *static_cast<Console::Context*>(lua_touserdata(state, -1));
    }

#include "LuaContentBindings.h"
}

namespace Lua
{
    struct State::Impl : public lua_State
    {
    };

    State::State()
        : mImpl(nullptr)
    {
        mImpl = static_cast<Impl*>(luaL_newstate());
        luaL_openlibs(mImpl);
    }

    State::~State()
    {
        if (mImpl)
            lua_close(mImpl);
    }

    void State::loadConsoleBindings(Console::Context& context)
    {
        lua_pushglobaltable(mImpl);
        luaL_setfuncs(mImpl, Console::lua_functions, 0);
        Console::set_context(mImpl, context);
    }

    void State::loadContentBindings(Console::Context& context)
    {
        lua_pushglobaltable(mImpl);
        luaL_setfuncs(mImpl, Content::lua_functions, 0);
        Content::set_context(mImpl, context);
    }

    void State::push(bool value)
    {
        lua_pushboolean(mImpl, value);
    }

    void State::push(int value)
    {
        lua_pushinteger(mImpl, value);
    }

    void State::push(float value)
    {
        lua_pushnumber(mImpl, value);
    }

    void State::push(const void* value)
    {
        lua_pushlightuserdata(mImpl, const_cast<void*>(value));
    }

    void State::pop(bool& value)
    {
        read(value, -1);
        lua_pop(mImpl, 1);
    }

    void State::pop(int& value)
    {
        read(value, -1);
        lua_pop(mImpl, 1);
    }

    void State::pop(float& value)
    {
        read(value, -1);
        lua_pop(mImpl, 1);
    }

    void State::read(bool& value, int index)
    {
        if (!lua_isboolean(mImpl, index))
            lua_error(mImpl);
        value = lua_toboolean(mImpl, index) != 0;
    }

    void State::read(int& value, int index)
    {
        if (!lua_isnumber(mImpl, index))
            lua_error(mImpl);
        value = static_cast<int>(lua_tonumber(mImpl, index));
    }

    void State::read(float& value, int index)
    {
        if (!lua_isnumber(mImpl, index))
            lua_error(mImpl);
        value = static_cast<float>(lua_tonumber(mImpl, index));
    }

    int State::getTop()
    {
        return lua_gettop(mImpl);
    }

    void State::doFile(const char* filename)
    {
        luaL_dofile(mImpl, filename);
    }

    void State::doString(const char* script)
    {
        luaL_dostring(mImpl, script);
    }

    void State::pushFunction(const char* function)
    {
        lua_getglobal(mImpl, function);
    }

    void State::callFunction(int numArgs, int numRet)
    {
        lua_call(mImpl, numArgs, numRet);
    }
}
