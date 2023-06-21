#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"
#include "common.h"

UIContext* UIContext_Create(Arena* arena)
{
    UIContext* context = (UIContext*)Arena_Acquire(arena, sizeof(UIContext)); 
    *context = (UIContext){
        .arena = arena,
        .drawCommands = NULL,
        .drawCommandCount = 0,
        .drawCommandCapacity = 0
    };
    return context;
}

void UIContext_NewFrame(UIContext* context)
{
    if (context)
    {
        context->drawCommandCount = 0;
    }
}

void UIContext_EndFrame(UIContext* context)
{
    if (context)
    {
        
    }
}

void UIContext_Render(UIContext* context)
{
    if (context)
    {
        UIDrawCommand* commands = context->drawCommands;
        for (int32_t i = 0, n = context->drawCommandCount; i < n; i++)
        {
            UIDrawCommand command = commands[i];
            if (command.active)
            {
                DrawRectangleRec(command.rect, WHITE);
            }
            else if (command.hover)
            {
                DrawRectangleLinesEx(command.rect, 3.0f, WHITE);
            }
            else
            {
                DrawRectangleLinesEx(command.rect, 1.0f, WHITE);
            }

            int textWidth = MeasureText(command.text, 16);
            DrawText(
                command.text, 
                command.rect.x + (command.rect.width - textWidth) / 2, 
                command.rect.y + (command.rect.height - 8) / 2, 
                16, 
                WHITE
            );
        }
    }
}

bool UIButton(UIContext* context, const char* text)
{
    const Rectangle rect = {
        .x = 100,
        .y = 100,
        .width = 200,
        .height = 60
    };

    const int mouseX = GetMouseX();
    const int mouseY = GetMouseY();
    const bool hover = !(mouseX < rect.x || mouseX > (rect.x + rect.width) || mouseY < rect.y || mouseY > (rect.y + rect.height));
    const bool clicked = hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    // Add command

    if (context)
    {
        if (context->drawCommandCount + 1 > context->drawCommandCapacity)
        {
            int32_t newCapacity = context->drawCommandCapacity * 2;
            if (newCapacity < 32)
            {
                newCapacity = 32;
            }

            void* newMemory = Arena_Acquire(context->arena, newCapacity * sizeof(UIDrawCommand));
            assert(newMemory != NULL);
            
            memcpy(newMemory, context->drawCommands, context->drawCommandCapacity * sizeof(UIDrawCommand));
            context->drawCommands = newMemory;
            context->drawCommandCapacity = newCapacity;
        }

        context->drawCommands[context->drawCommandCount++] = (UIDrawCommand){
            .text = text,
            .rect = rect,
            .hover = hover,
            .active = hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT)
        };
    }

    return clicked;
}
