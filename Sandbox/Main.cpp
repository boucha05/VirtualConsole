#include <stdio.h>
#include "Application.h"
#include "Console.h"

class Sandbox : public Application
{
protected:
    void init()
    {
        colorcount(16);
        colortable(black, 0, 0, 0);
        colortable(dark_blue, 32, 51, 123);
        colortable(dark_purple, 126, 37, 83);
        colortable(dark_green, 0, 144, 61);
        colortable(brown, 171, 82, 54);
        colortable(dark_gray, 52, 54, 53);
        colortable(light_gray, 194, 195, 199);
        colortable(white, 255, 241, 232);
        colortable(red, 255, 0, 77);
        colortable(orange, 255, 155, 0);
        colortable(yellow, 255, 231, 39);
        colortable(green, 0, 226, 50);
        colortable(blue, 41, 173, 255);
        colortable(indigo, 132, 112, 169);
        colortable(pink, 255, 119, 168);
        colortable(peach, 255, 214, 197);
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
};

int main()
{
    Sandbox sandbox;
    return sandbox.run();
}