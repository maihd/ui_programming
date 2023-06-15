#include <raylib.h>
#include "HotDylibApi.h"

HOTDYLIB_EXPORT void* LibEntry(void* data, HotDylibState newState, HotDylibState oldState)
{
    switch (newState)
    {
        case HOTDYLIB_INIT:
            break;

        case HOTDYLIB_RELOAD:
            break;

        case HOTDYLIB_UNLOAD:
            break;

        case HOTDYLIB_QUIT:
            break;

        default:
            break;
    }
    return 0;
}

HOTDYLIB_EXPORT void Update(float dt)
{

}

HOTDYLIB_EXPORT void Draw()
{
    ClearBackground(BLACK);
    DrawText("Hello world HMS!", 10, 10, 16, WHITE);
}
