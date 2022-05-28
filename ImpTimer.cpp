#include "ImpTimer.h"
#include "CommonFunc.h"

ImpTimer::ImpTimer()
{
    startTick = 0;
    pausedTick = 0;
    isPaused = false;
    isStarted = false;
}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::start()
{
    isStarted = true;
    isPaused = false;
    startTick = SDL_GetTicks();
}

void ImpTimer::stop()
{
    isPaused = false;
    isStarted = false;
}

void ImpTimer::paused()
{
    if (isStarted == true && isPaused == false)
    {
        isPaused = true;
        pausedTick = SDL_GetTicks() - startTick;
    }
}

void ImpTimer::unpaused()
{
    if (isPaused == true)
    {
        isPaused = false;
        startTick = SDL_GetTicks() - pausedTick;
        pausedTick = 0;
    }
}

int ImpTimer::get_ticks()
{
    if (isStarted == true)
    {
        if (isPaused == true)
        {
            return pausedTick;
        }
        else
        {
            return SDL_GetTicks() - startTick;
        }
    }

    return 0;
}

bool ImpTimer::is_started()
{
    return isStarted;
}

bool ImpTimer::is_paused()
{
    return isPaused;
}
