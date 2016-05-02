#pragma once

#include <functional>

namespace Console
{
    class Context;
}

namespace Lua
{
    class State
    {
    public:
        State();
        ~State();
        void setContext(Console::Context& context);
        void push(bool value);
        void push(int value);
        void push(float value);
        void push(const void* value);
        void pop(bool& value);
        void pop(int& value);
        void pop(float& value);
        void read(bool& value, int index);
        void read(int& value, int index);
        void read(float& value, int index);
        int getTop();
        void doFile(const char* filename);
        void doString(const char* script);

        void push()
        {
        }

        template <typename T, typename... TArgs>
        void push(const T value, const TArgs... args)
        {
            push(value);
            push(args...);
        }

        template <typename T, typename... TArgs>
        void pop(T& value, TArgs&... args)
        {
            pop(args...);
            pop(value);
        }

        template <typename TRet, typename... TArgs>
        TRet call(const char* function, TArgs... args)
        {
            pushFunction(function);
            push(args...);
            callFunction(sizeof...(TArgs), 1);
            TRet result;
            pop(result);
            return result;
        }

        template <typename... TArgs>
        void callv(const char* function, TArgs... args)
        {
            pushFunction(function);
            push(args...);
            callFunction(sizeof...(TArgs), 0);
        }

    private:
        struct Impl;

        void pushFunction(const char* function);
        void callFunction(int numArgs, int numRet);

        Impl*   mImpl;
    };
}
