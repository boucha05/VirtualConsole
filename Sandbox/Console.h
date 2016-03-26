#pragma once

namespace Console
{
    struct Context;

    struct Config
    {
        int     screenWidth;
        int     screenHeight;
        int     windowWidth;
        int     windowHeight;

        Config()
            : screenWidth(640)
            , screenHeight(360)
            , windowWidth(1280)
            , windowHeight(720)
        {
        }
    };

    Context* createContext(const Config& config);
    void destroyContext(Context& context);
    bool isActive(Context& context);

    void flip(Context& context);
    void clip(Context& context, int x, int y, int w, int h);
    void color(Context& context, int value);
    void colorcount(Context& context, int value);
    void colortable(Context& context, int index, int r, int g, int b);
    void cls(Context& context);
    void camera(Context& context, int x, int y);
    void rect(Context& context, int x, int y, int w, int h);
    void rectfill(Context& context, int x, int y, int w, int h);
    void memsize(Context& context, int size);
    void memload(Context& context, int offset, const void* src, int size);
    void sprsheet(Context& context, int offset, int bits, int sizex, int sizey, int countx, int county);
    void spr(Context& context, int n, int x, int y, int w, int h, bool flip_x, bool flip_y);
}
