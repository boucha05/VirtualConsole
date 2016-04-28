#include "LuaState.h"

extern "C" {
#include <Contrib/lua-5.2.4/src/lauxlib.h>
}

#include "Console.h"

#define VERIFY(expr)    if(expr) ; else return false

namespace
{
    class LuaStateImpl : public LuaState
    {
    public:
        LuaStateImpl()
            : mState(nullptr)
            , mContext(nullptr)
            , mValid(false)
        {
            mValid = create();
        }

        ~LuaStateImpl()
        {
            destroy();
        }

        bool isValid() const
        {
            return mValid;
        }

        virtual bool openConsole(Console::Context& context) override
        {
            mContext = &context;
            return true;
        }

    private:
        bool create()
        {
            mState = luaL_newstate();
            VERIFY(mState);
            return true;
        }

        void destroy()
        {
            if (mState)
                lua_close(mState);
        }

        lua_State*          mState;
        Console::Context*   mContext;
        bool                mValid;
    };
}

LuaState* LuaState::create()
{
    auto instance = new LuaStateImpl();
    if (!instance->isValid())
    {
        delete instance;
        instance = nullptr;
    }
    return instance;
}

void LuaState::destroy(LuaState& instance)
{
    delete &static_cast<LuaStateImpl&>(instance);
}
