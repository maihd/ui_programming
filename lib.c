#include <stdio.h>
#include <raylib.h>

#include "common.h"
#include "HotDylibApi.h"

HOTDYLIB_EXPORT Arena* LibEntry(Arena* arena, HotDylibState newState, HotDylibState oldState)
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

    if (arena == NULL)
    {
        arena = Arena_CreateDefault();
    }
    else
    {
        TraceLog(LOG_INFO, "Arena have been created!");
    }

    return arena;
}

HOTDYLIB_EXPORT void Update(float dt)
{

}

HOTDYLIB_EXPORT void Draw()
{
    ClearBackground(BLACK);
    DrawText("Hello world HMS 3!", 10, 10, 16, WHITE);
}
