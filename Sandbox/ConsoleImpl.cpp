#include "ConsoleImpl.h"
#include <algorithm>

namespace
{
    struct SDLInstance
    {
        static bool initialized()
        {
            static SDLInstance instance;
            return instance.valid();
        }

        SDLInstance()
        {
            SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        }

        ~SDLInstance()
        {
            SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        }

        bool valid()
        {
            return true;
        }
    };
}

namespace Console
{
    void Point::set(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    void Point::add(const Point& p)
    {
        x += p.x;
        y += p.y;
    }

    void Point::sub(const Point& p)
    {
        x -= p.x;
        y -= p.y;
    }

    ///////////////////////////////////////////////////////////////////////////

    void Rect::set(int _x, int _y, int _width, int _height)
    {
        pos.set(_x, _y);
        if ((_width < 0) || (_height < 0))
            size.set(0, 0);
        else
            size.set(_width, _height);
    }

    void Rect::corners(const Point& p0, const Point& p1)
    {
        pos = p0;

    }

    void Rect::intersection(const Rect& r1, const Rect& r2)
    {
        pos.x = std::max(r1.pos.x, r2.pos.x);
        pos.y = std::max(r1.pos.y, r2.pos.y);
        size.x = std::min(r1.pos.x + r1.size.x, r2.pos.x + r2.size.x) - pos.x;
        size.y = std::min(r1.pos.y + r1.size.y, r2.pos.y + r2.size.y) - pos.y;
        if ((size.x < 0) || (size.y < 0))
            size.set(0, 0);
    }

    bool Rect::empty() const
    {
        return (size.x <= 0) || (size.y <= 0);
    }

    ///////////////////////////////////////////////////////////////////////////

    void Context::initialize()
    {
        mActive = false;
        mWindow = nullptr;
        mRenderer = nullptr;
        mTexture = nullptr;
    }

    bool Context::create(const Config& config)
    {
        destroy();

        VERIFY(SDLInstance::initialized());

        mScreen.set(0, 0, config.screenWidth, config.screenHeight);
        mWindow = SDL_CreateWindow("Virtual Console", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config.windowWidth, config.windowHeight, SDL_WINDOW_RESIZABLE);
        VERIFY(mWindow);

        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        VERIFY(mRenderer);

        mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, config.screenWidth, config.screenHeight);
        VERIFY(mTexture);

        mFrame.resize(config.screenWidth * config.screenHeight, 0);

        mActive = true;

        reboot();
        update();

        return true;
    }

    void Context::destroy()
    {
        if (mTexture)
            SDL_DestroyTexture(mTexture);
        if (mRenderer)
            SDL_DestroyRenderer(mRenderer);
        if (mWindow)
            SDL_DestroyWindow(mWindow);
        initialize();
    }

    void Context::update()
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_WINDOWEVENT)
            {
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    mActive = false;
                    break;
                }
            }
        }
    }

    bool Context::isActive()
    {
        return mActive;
    }

    void Context::reboot()
    {
        mClip = mScreen;
        mCamera.set(0, 0);
        mColor = 0;
        mColorTable.clear();
    }

    void Context::flip()
    {
        SDL_UpdateTexture(mTexture, nullptr, mFrame.data(), mScreen.size.x * sizeof(uint32_t));
        SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);
        SDL_RenderPresent(mRenderer);
        update();
    }

    void Context::clip(int x, int y, int w, int h)
    {
        Rect rect;
        rect.set(x, y, w, h);
        mClip.intersection(rect, mScreen);
    }

    void Context::color(int value)
    {
        mColor = value;
    }

    void Context::colorcount(int value)
    {
        mColorTable.resize(value, 0);
    }

    void Context::colortable(int index, int r, int g, int b)
    {
        if (static_cast<size_t>(index) < mColorTable.size())
        {
            const uint8_t components[] = { static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b), 255 };
            mColorTable[index] = *reinterpret_cast<const uint32_t*>(components);
        }
    }

    void Context::cls()
    {
        uint32_t value = mColorTable[mColor];
        uint32_t* row = mFrame.data() + mClip.pos.x + mClip.pos.y * mScreen.size.x;
        for (int y = 0; y < mClip.size.y; ++y)
        {
            for (int x = 0; x < mClip.size.x; ++x)
                row[x] = value;
            row += mScreen.size.x;
        }
    }

    void Context::camera(int x, int y)
    {
        mCamera.set(x, y);
    }

    void Context::rect(int x, int y, int w, int h)
    {
        Rect rect;
        rect.set(mCamera.x + x, mCamera.y + y, w, h);
        Rect region;
        region.intersection(rect, mClip);
        if (region.empty())
            return;

        uint32_t value = mColorTable[mColor];
        uint32_t* row = mFrame.data() + region.pos.x + region.pos.y * mScreen.size.x;
        if (region.pos.y <= rect.pos.y)
        {
            for (int x = 0; x < region.size.x; ++x)
                row[x] = value;
        }

        if (region.pos.x <= rect.pos.x)
        {
            uint32_t* col = row;
            for (int y = 0; y < region.size.y; ++y)
            {
                col[0] = value;
                col += mScreen.size.x;
            }
        }

        if (region.pos.x + region.size.x >= rect.pos.x + rect.size.x)
        {
            uint32_t* col = row + region.size.x - 1;
            for (int y = 0; y < region.size.y; ++y)
            {
                col[0] = value;
                col += mScreen.size.x;
            }
        }

        row += (region.size.y - 1) * mScreen.size.x;
        if (region.pos.y + region.size.y >= rect.pos.y + rect.size.y)
        {
            for (int x = 0; x < region.size.x; ++x)
                row[x] = value;
        }
    }

    void Context::rectfill(int x, int y, int w, int h)
    {
        Rect rect;
        rect.set(mCamera.x + x, mCamera.y + y, w, h);
        Rect region;
        region.intersection(rect, mClip);

        uint32_t value = mColorTable[mColor];
        uint32_t* row = mFrame.data() + region.pos.x + region.pos.y * mScreen.size.x;
        for (int y = 0; y < region.size.y; ++y)
        {
            for (int x = 0; x < region.size.x; ++x)
                row[x] = value;
            row += mScreen.size.x;
        }
    }
}