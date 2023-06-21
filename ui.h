#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <raylib.h>
#include "common.h"

typedef struct UIDrawCommand
{
    const char* text;
    Rectangle   rect;

    bool        hover;
    bool        active;
} UIDrawCommand;

typedef struct UIContext
{
    Arena*          arena;

    UIDrawCommand*  drawCommands;
    int32_t         drawCommandCount;
    int32_t         drawCommandCapacity;
} UIContext;

UIContext*  UIContext_Create(Arena* arena);
void        UIContext_Destroy(UIContext* context);

void        UIContext_NewFrame(UIContext* context);
void        UIContext_EndFrame(UIContext* context);
void        UIContext_Render(UIContext* context);

bool        UIButton(UIContext* context, const char* string);
