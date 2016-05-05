#include "Application.h"

using namespace Console;

Application::Application()
{
    initialize();
}

Application::~Application()
{
    destroy();
}

void Application::initialize()
{
    mContext = nullptr;
}

bool Application::create()
{
    destroy();
    Config config;
    mContext.reset(new Context(config));
    VERIFY(mContext->isValid());
    return true;
}

void Application::destroy()
{
    if (mContext)
        mContext.reset();
    initialize();
}

bool Application::run()
{
    VERIFY(create());
    init();
    while (mContext && mContext->isActive())
    {
        update();
        render();
        mContext->flip();
    }
    return true;
}
