#pragma once

#include "Console.h"
#include <SDL.h>
#include <stdint.h>
#include <vector>

#define VERIFY(expr)    if(expr) ; else return false

namespace Console
{
    struct Point
    {
        int             x;
        int             y;

        void set(int _x, int _y);
        void add(const Point& p);
        void sub(const Point& p);
    };

    struct Rect
    {
        Point           pos;
        Point           size;

        void set(int _x, int _y, int _width, int _height);
        void corners(const Point& p0, const Point& p1);
        void intersection(const Rect& r1, const Rect& r2);
        bool empty() const;
    };

    struct Context
    {
        void initialize();
        bool create(const Config& config);
        void destroy();
        void update();
        bool isActive();
        void reboot();

        void flip();
        void clip(int x, int y, int w, int h);
        void color(int value);
        void colorcount(int value);
        void colortable(int index, int r, int g, int b);
        void cls();
        void camera(int x, int y);
        void rect(int x, int y, int w, int h);
        void rectfill(int x, int y, int w, int h);

        bool                    mActive : 1;
        SDL_Window*             mWindow;
        SDL_Renderer*           mRenderer;
        SDL_Texture*            mTexture;
        Rect                    mScreen;
        Rect                    mClip;
        Point                   mCamera;
        uint32_t                mColor;
        std::vector<uint32_t>   mFrame;
        std::vector<uint32_t>   mColorTable;
    };
}
