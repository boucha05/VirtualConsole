#include <stdio.h>
#include "Application.h"
#include "Console.h"

namespace
{
    static const char sprite_sheet[] =
    {
#include "Content/SpriteSheet.h"
    };
}

class Sandbox : public Application
{
protected:
    void init()
    {
        colorcount(16);
        colortable(black, 0, 0, 0);
        colortable(dark_blue, 29, 43, 83);
        colortable(dark_purple, 126, 37, 83);
        colortable(dark_green, 0, 135, 41);
        colortable(brown, 171, 82, 54);
        colortable(dark_gray, 95, 87, 79);
        colortable(light_gray, 194, 195, 199);
        colortable(white, 255, 241, 232);
        colortable(red, 255, 0, 77);
        colortable(orange, 255, 163, 0);
        colortable(yellow, 255, 255, 39);
        colortable(green, 0, 231, 86);
        colortable(blue, 41, 173, 255);
        colortable(indigo, 131, 118, 156);
        colortable(pink, 255, 119, 168);
        colortable(peach, 255, 204, 170);

        memsize(mem_size);
        memload(mem_sprite_addr, sprite_sheet, sizeof(sprite_sheet));
    }

    void update()
    {
    }

    void render()
    {
        color(dark_blue);
        cls();

        camera(10, 10);
        for (int y = 0; y < 4; ++y)
        {
            for (int x = 0; x < 4; ++x)
            {
                int c = y * 4 + x;
                color(c);
                rectfill(x * 50, y * 50, 40, 40);

                color(15 - c);
                rect(x * 50, y * 50, 40, 40);
            }
        }

        camera(210, 10);
        sprsheet(mem_sprite_addr, 4, 8, 8, 16, 16);
        spr(0, 0, 0, 16, 16);
    }

    enum
    {
        black,
        dark_blue,
        dark_purple,
        dark_green,
        brown,
        dark_gray,
        light_gray,
        white,
        red,
        orange,
        yellow,
        green,
        blue,
        indigo,
        pink,
        peach,
    };

    enum
    {
        mem_sprite_addr = 0x0000,
        mem_sprite_size = 128 * 128 * 4,
        mem_size = mem_sprite_addr + mem_sprite_size
    };
};

int main()
{
    Sandbox sandbox;
    return sandbox.run();
}