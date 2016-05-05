#include <assert.h>
#include <stdio.h>
#include "Application.h"
#include "Console.h"

class Sandbox : public Application
{
protected:
    void init()
    {
        lua().loadContentBindings(context());
        lua().doFile("Sandbox.lua");
        lua().loadConsoleBindings(context());
        lua().callv("init");
    }

    void update()
    {
        lua().callv("update");
    }

    void render()
    {
        lua().callv("render");
    }
};

int main()
{
    Sandbox sandbox;
    return sandbox.run();
}