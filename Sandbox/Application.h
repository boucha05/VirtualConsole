#pragma once

#include "Console.h"
#include "LuaState.h"

#define VERIFY(expr)    if(expr) ; else return false

class Application
{
public:
    Application();
    virtual ~Application();
    bool create();
    void destroy();
    bool run();

    void flip()
    {
        Console::flip(*mContext);
    }

    void clip(int x, int y, int w, int h)
    {
        Console::clip(*mContext, x, y, w, h);
    }

    void color(int value)
    {
        Console::color(*mContext, value);
    }

    void colorcount(int value)
    {
        Console::colorcount(*mContext, value);
    }

    void colortable(int index, int r, int g, int b)
    {
        Console::colortable(*mContext, index, r, g, b);
    }

    void cls()
    {
        Console::cls(*mContext);
    }

    void camera(int x, int y)
    {
        Console::camera(*mContext, x, y);
    }

    void rect(int x, int y, int w, int h)
    {
        Console::rect(*mContext, x, y, w, h);
    }

    void rectfill(int x, int y, int w, int h)
    {
        Console::rectfill(*mContext, x, y, w, h);
    }

    void memsize(int size)
    {
        Console::memsize(*mContext, size);
    }

    void memload(int offset, const void* src, int size)
    {
        Console::memload(*mContext, offset, src, size);
    }

    void bmpload(int offset, int stride, int bits, int shift, const void* src, int sizex, int sizey)
    {
        Console::bmpload(*mContext, offset, stride, bits, shift, src, sizex, sizey);
    }

    void sprsheet(int offset, int bits, int shift, int sizex, int sizey, int countx, int county)
    {
        Console::sprsheet(*mContext, offset, bits, shift, sizex, sizey, countx, county);
    }

    void spr(int n, int x, int y, int w, int h, bool flip_x = false, bool flip_y = false)
    {
        Console::spr(*mContext, n, x, y, w, h, flip_x, flip_y);
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

    Console::Context*   mContext;
    Lua::State          mLua;
};
