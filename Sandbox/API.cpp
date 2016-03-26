#include "Console.h"
#include "ConsoleImpl.h"

namespace Console
{
    Context* createContext(const Config& config)
    {
        auto console = new Context();
        console->initialize();
        if (!console->create(config))
        {
            delete console;
            console = nullptr;
        }
        return console;
    }

    void destroyContext(Context& context)
    {
        context.destroy();
        delete &context;
    }

    bool isActive(Context& context)
    {
        return context.isActive();
    }

    void flip(Context& context)
    {
        context.flip();
    }

    void clip(Context& context, int x, int y, int w, int h)
    {
        context.clip(x, y, w, h);
    }

    void color(Context& context, int value)
    {
        context.color(value);
    }

    void colorcount(Context& context, int value)
    {
        context.colorcount(value);
    }

    void colortable(Context& context, int index, int r, int g, int b)
    {
        context.colortable(index, r, g, b);
    }

    void cls(Context& context)
    {
        context.cls();
    }

    void camera(Context& context, int x, int y)
    {
        context.camera(x, y);
    }

    void rect(Context& context, int x, int y, int w, int h)
    {
        context.rect(x, y, w, h);
    }

    void rectfill(Context& context, int x, int y, int w, int h)
    {
        context.rectfill(x, y, w, h);
    }
}