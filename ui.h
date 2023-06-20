#pragma once

#include <stdint.h>

typedef struct UIContext
{
    uint8_t padding[4];
} UIContext;

void UIContext_NewFrame(UIContext* context);
void UIContext_EndFrame(UIContext* context);
void UIContext_Render(UIContext* context);
