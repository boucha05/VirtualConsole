#include "Console.h"
#include <SDL_bits.h>
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

    bool isPowerOf2(int value)
    {
        return (value >= 0) && ((value & (value - 1)) == 0);
    }

    int getPowerOf2(int value)
    {
        return SDL_MostSignificantBitIndex32(value);
    }
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

    Context::Context(const Config& config)
    {
        initialize();
        if (!create(config))
            destroy();
    }

    Context::~Context()
    {
        destroy();
    }

    void Context::initialize()
    {
        mValid = false;
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
        mWindow = SDL_CreateWindow("Virtual Console", 100, 100, config.windowWidth, config.windowHeight, SDL_WINDOW_RESIZABLE);
        VERIFY(mWindow);

        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        VERIFY(mRenderer);

        mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, config.screenWidth, config.screenHeight);
        VERIFY(mTexture);

        mFrame.resize(config.screenWidth * config.screenHeight, 0);

        mActive = true;
        mValid = true;

        reboot();
        update();

        return true;
    }

    void Context::destroy()
    {
        clearUserData();
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

    bool Context::isValid()
    {
        return mValid;
    }

    bool Context::isActive()
    {
        return mActive;
    }

    void Context::reboot()
    {
        mColorTable.clear();
        mMemory.clear();

        clip(0, 0, mScreen.size.x, mScreen.size.y);
        camera(0, 0);
        color(0);
        sprsheet(0, 0, 0, 0, 0, 0, 0);
    }

    UserData* Context::createUserData(UserData::Type type)
    {
        auto userData = new UserData();
        userData->type = type;
        userData->data = nullptr;

        switch (type)
        {
        case UserData::Type::Binary:
            userData->data = new Binary();
            break;

        default:
            ASSERT(false);
        }

        mUserData.insert(userData);
        return userData;
    }

    void Context::destroyUserData(UserData* userData)
    {
        if (!userData)
            return;

        switch (userData->type)
        {
        case UserData::Type::Binary:
            delete static_cast<Binary*>(userData->data);
            break;

        default:
            ASSERT(false);
        }

        if (!mUserData.erase(userData))
            delete userData;
    }

    void Context::clearUserData()
    {
        for (auto userData : mUserData)
            delete userData;
        mUserData.clear();
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

    void Context::memsize(int size)
    {
        mMemory.resize(size, 0);
    }

    void Context::memcopy(int offset, int src, int size)
    {
        int maxSize = static_cast<int>(mMemory.size()) - offset;
        size = std::min(maxSize, size);
        if (size > 0)
            memcpy(mMemory.data() + offset, mMemory.data() + src, size);
    }

    void* Context::importbinary(const char* filename)
    {
        auto userData = createUserData(UserData::Type::Binary);
        auto binary = static_cast<Binary*>(userData->data);
        if (binary)
        {
            FILE* file = fopen(filename, "rb");
            if (file)
            {
                fseek(file, 0, SEEK_END);
                int size = static_cast<int>(ftell(file));
                if (size > 0)
                {
                    fseek(file, 0, SEEK_SET);
                    binary->data.resize(size, 0);
                    size = static_cast<int>(fread(binary->data.data(), 1, size, file));
                    binary->data.resize(size, 0);
                }
                fclose(file);
            }
        }
        return userData;
    }

    int Context::fileload(int offset, const void* file, int start, int size)
    {
        auto userData = static_cast<const UserData*>(file);
        if (!userData || (userData->type != UserData::Type::Binary) || !userData->data)
            return 0;

        auto* binary = static_cast<Binary*>(userData->data);

        int maxSize = static_cast<int>(mMemory.size()) - offset;
        if (maxSize <= 0)
            return 0;

        int readSize = static_cast<int>(binary->data.size());
        if (readSize > 0)
        {
            if (size <= 0)
                size = readSize;

            readSize = std::min(readSize, maxSize);
            if (readSize > 0)
            {
                memcpy(mMemory.data() + offset, binary->data.data(), readSize);
            }
        }
        return readSize;
    }

    void Context::bmpload(int offset, int stride, int bits, int shift, int src, int sizex, int sizey)
    {
        bits = ((1 << bits) - 1) << shift;
        ASSERT(static_cast<size_t>(offset + stride * sizey + sizex) <= mMemory.size());
        auto srcMem = static_cast<const uint8_t*>(mMemory.data() + src);
        auto dstMem = static_cast<uint8_t*>(mMemory.data() + offset);
        for (int y = 0; y < sizey; ++y)
        {
            for (int x = 0; x < sizex; ++x)
            {
                auto srcData = *srcMem++ >> shift;
                dstMem[x] = (dstMem[x] & ~bits) | (srcData & bits);
            }
            dstMem += stride;
        }
    }

    void Context::sprsheet(int offset, int bits, int shift, int sizex, int sizey, int countx, int county)
    {
        ASSERT(isPowerOf2(sizex));
        ASSERT(sizex <= cMaxSpriteSize);
        ASSERT(isPowerOf2(sizey));
        ASSERT(sizey <= cMaxSpriteSize);
        ASSERT(isPowerOf2(countx));
        ASSERT(isPowerOf2(county));

        mSpriteOffset = offset;
        mSpriteBits = (1 << bits) - 1;
        mSpriteShift = shift;
        mLog2SpriteSize.set(getPowerOf2(sizex), getPowerOf2(sizey));
        mSpriteSize.set(sizex, sizey);
        mLog2SpriteCount.set(getPowerOf2(countx), getPowerOf2(county));
        mSpriteCount.set(countx, county);
        mLog2SpriteSheetSize = mLog2SpriteSize;
        mLog2SpriteSheetSize.add(mLog2SpriteCount);
        mSpriteSheetSize.set(1 << mLog2SpriteSheetSize.x, 1 << mLog2SpriteSheetSize.y);
        if (bits)
        {
            ASSERT(static_cast<size_t>(1 << (mLog2SpriteSheetSize.x + mLog2SpriteSheetSize.y)) <= mMemory.size());
        }
    }

    void Context::spr(int n, int x, int y, int w, int h, bool flip_x, bool flip_y)
    {
        Point sprite;
        sprite.x = n & (mSpriteCount.x - 1);
        sprite.y = n >> mLog2SpriteCount.x;
        ASSERT((sprite.x + w) <= mSpriteCount.x);
        ASSERT((sprite.y + h) <= mSpriteCount.y);

        Rect rect;
        rect.set(x, y, w << mLog2SpriteSize.x, h << mLog2SpriteSize.y);
        rect.pos.add(mCamera);
        Rect region;
        region.intersection(rect, mClip);
        Point pos = region.pos;
        pos.sub(mCamera);

        Point pitch;
        pitch.x = 1;
        pitch.y = mSpriteSheetSize.x;
        if (flip_x)
        {
            pos.x = mSpriteSheetSize.x - 1 - pos.x;
            pitch.x = -pitch.x;
        }
        if (flip_y)
        {
            pos.y = mSpriteSheetSize.y - 1 - pos.y;
            pitch.y = -pitch.y;
        }

        int srcOffset = mSpriteOffset + pos.x + (pos.y << mLog2SpriteSheetSize.x);
        int dstOffset = region.pos.x + (region.pos.y * mScreen.size.x);
        for (int posy = 0; posy < region.size.y; ++posy)
        {
            int src = srcOffset;
            for (int posx = 0; posx < region.size.x; ++posx)
            {
                uint8_t value = (mMemory[src] >> mSpriteShift) & mSpriteBits;
                src += pitch.x;
                uint32_t pixel = mColorTable[value];
                mFrame[dstOffset + posx] = pixel;
            }

            srcOffset += pitch.y;
            dstOffset += mScreen.size.x;
        }
    }
}