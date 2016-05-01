#pragma once

#include "Console.h"
#include <SDL.h>
#include <assert.h>
#include <stdint.h>
#include <vector>

#define VERIFY(expr)    if(expr) ; else return false
#define ASSERT(expr)    (assert(expr))

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

#include "Bindings.h"

        static const int cLog2MaxSpriteSize = 6;
        static const int cMaxSpriteSize = 1 << cLog2MaxSpriteSize;

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
        std::vector<uint8_t>    mMemory;
        uint32_t                mSpriteOffset;
        uint32_t                mSpriteBits;
        uint32_t                mSpriteShift;
        Point                   mLog2SpriteSize;
        Point                   mSpriteSize;
        Point                   mLog2SpriteCount;
        Point                   mSpriteCount;
        Point                   mLog2SpriteSheetSize;
        Point                   mSpriteSheetSize;
    };
}
