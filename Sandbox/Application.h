#pragma once

#include "Console.h"

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

protected:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

private:
    void initialize();

    Console::Context*   mContext;
};
