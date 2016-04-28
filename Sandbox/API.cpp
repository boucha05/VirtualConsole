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

    void memsize(Context& context, int size)
    {
        context.memsize(size);
    }

    void memload(Context& context, int offset, const void* src, int size)
    {
        context.memload(offset, src, size);
    }

    void bmpload(Context& context, int offset, int stride, int bits, int shift, const void* src, int sizex, int sizey)
    {
        context.bmpload(offset, stride, bits, shift, src, sizex, sizey);
    }

    void sprsheet(Context& context, int offset, int bits, int shift, int sizex, int sizey, int countx, int county)
    {
        context.sprsheet(offset, bits, shift, sizex, sizey, countx, county);
    }

    void spr(Context& context, int n, int x, int y, int w, int h, bool flip_x, bool flip_y)
    {
        context.spr(n, x, y, w, h, flip_x, flip_y);
    }
}