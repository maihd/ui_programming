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

static LibState* CreateLibState(Arena* arena)
{
    LibState* state = (LibState*)Arena_Acquire(arena, sizeof(LibState));
    state->hotReloadCount = 0;
    state->arena = arena;
    state->context = UIContext_Create(state->arena);
    return state;
}

HOTDYLIB_EXPORT
LibState* LibEntry(LibState* state, HotDylibState newState, HotDylibState oldState)
{
    TraceLog(LOG_INFO, "LibEntry, state = %p", state);

    Arena* arena = Arena_GetScratch();

    switch (newState)
    {
        case HOTDYLIB_INIT:
            TraceLog(LOG_INFO, "LibEntry: enter init");
            //state = (UIState*)Arena_CreateDefault();
            if (state != NULL)
            {
                state->hotReloadCount = 0;
                state->context = UIContext_Create(state->arena);
                state->arena = Arena_GetScratch();
            }
            else
            {
                state = CreateLibState(arena);
            }
            g_state = state;
            break;

        case HOTDYLIB_RELOAD:
            TraceLog(LOG_INFO, "LibEntry: enter reload");
            g_state = state;
            Arena_Clear(arena);
            if (state != NULL)
            {
                state->hotReloadCount++;
                TraceLog(LOG_INFO, "Arena have been created, reload count = %d!", state->hotReloadCount);

                if (state->context == NULL)
                {
                    state->context = UIContext_Create(state->arena);
                }
            }
            else
            {
                state = CreateLibState(arena);
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

    // test HotDylib handling fatal error
    // char* null = 0;
    // *null = 0;

    return state;
}

HOTDYLIB_EXPORT
void Update(float dt)
{
    if (g_state)
    {
        UIContext_NewFrame(g_state->context);
        {
            if (UIButton(g_state->context, "Click Me!"))
            {
                TraceLog(LOG_INFO, "Clicked ME!");
            }

            if (UIButtonV(g_state->context, "Click Me Too!", (Vector2){ .x = 100, .y = 200 }))
            {
                TraceLog(LOG_INFO, "Clicked ME too!");
            }
        }
        UIContext_EndFrame(g_state->context);
    }
}

HOTDYLIB_EXPORT
void Draw()
{
    ClearBackground(BLACK);

    if (g_state != NULL)
    {
        // Render UI components
        UIContext_Render(g_state->context);

        // Render Debug information
        const char* text = TextFormat("Reload Count: %d", g_state->hotReloadCount);
        DrawTextEx(g_state->context->font, text, (Vector2){ .x = 10, .y = 10 }, 16.0f, 0.0f, WHITE);

        const char* fps = TextFormat("FPS: %d", GetFPS());
        DrawTextEx(g_state->context->font, fps, (Vector2){ .x = 10, .y = 30 }, 16.0f, 0.0f, WHITE);
    }
}
