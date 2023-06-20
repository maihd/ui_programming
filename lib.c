#include <stdio.h>
#include <raylib.h>

#include "common.h"
#include "HotDylibApi.h"

#include "ui.h"

typedef struct LibState
{
    Arena*      arena;
    UIContext*  context;
    int32_t     hotReloadCount;
} LibState;

static LibState* g_state = NULL;

HOTDYLIB_EXPORT 
LibState* LibEntry(LibState* state, HotDylibState newState, HotDylibState oldState)
{
    TraceLog(LOG_INFO, "LibEntry, state = %p", state);

    switch (newState)
    {
        case HOTDYLIB_INIT:
            TraceLog(LOG_INFO, "LibEntry: enter init");
            //state = (UIState*)Arena_CreateDefault();
            if (state != NULL)
            {
                state->hotReloadCount = 0;
                state->context = NULL;
                state->arena = Arena_GetScratch();
            }
            else
            {
                Arena* arena = Arena_GetScratch();
                state = (LibState*)Arena_Acquire(arena, sizeof(LibState));
                state->hotReloadCount = 0;
                state->arena = arena;
                state->context = NULL;
            }
            g_state = state;
            break;

        case HOTDYLIB_RELOAD:
            TraceLog(LOG_INFO, "LibEntry: enter reload");
            g_state = state;
            if (state != NULL)
            {
                state->hotReloadCount++;
                TraceLog(LOG_INFO, "Arena have been created, reload count = %d!", state->hotReloadCount);
            }
            break;

        case HOTDYLIB_UNLOAD:
            TraceLog(LOG_INFO, "LibEntry: enter unload");
            break;

        case HOTDYLIB_QUIT:
            TraceLog(LOG_INFO, "LibEntry: enter quit");
            if (state != NULL)
            {
                Arena_Destroy(state->arena);
                state = NULL;
            }
            break;

        default:
            break;
    }

    return state;
}

HOTDYLIB_EXPORT void Update(float dt)
{
    if (g_state)
    {
        UIContext_NewFrame(g_state->context);
        UIContext_EndFrame(g_state->context);
    }
}

HOTDYLIB_EXPORT void Draw()
{
    ClearBackground(BLACK);

    if (g_state)
    {
        UIContext_Render(g_state->context);
    }
    
    const char* text;
    if (g_state != NULL)
    {
        text = TextFormat("Hello world HMS %d!", g_state->hotReloadCount);
    }
    else
    {
        text = "Hello world HMS!";
    }

    DrawText(text, 10, 10, 16, WHITE);
}
