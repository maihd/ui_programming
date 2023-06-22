#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"
#include "common.h"

UIContext* UIContext_Create(Arena* arena)
{
    Font font = LoadFont("assets/ubuntu-font-family-0.83/Ubuntu-R.ttf");
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    UIContext* context = (UIContext*)Arena_Acquire(arena, sizeof(UIContext));
    *context = (UIContext){
        .arena = arena,
        .drawCommands = NULL,
        .drawCommandCount = 0,
        .drawCommandCapacity = 0,

        .font = font,
    };
    return context;
}

void UIContext_NewFrame(UIContext* context)
{
    if (context)
    {
        context->uid = 0;
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
                DrawRectangleRounded(command.rect, 0.5f, 10, WHITE);
            }
            else if (command.hover)
            {
                DrawRectangleRoundedLines(command.rect, 0.5f, 10, 3.0f, WHITE);
            }
            else
            {
                DrawRectangleRoundedLines(command.rect, 0.5f, 10, 1.0f, WHITE);
            }

            float fontSize = 24.0f;
            Vector2 textSize = MeasureTextEx(context->font, command.text, fontSize, 0.0f);
            DrawTextEx(
                context->font,
                command.text,
                (Vector2){
                    .x = command.rect.x + (command.rect.width - textSize.x) / 2, 
                    .y = command.rect.y + (command.rect.height - textSize.y) / 2, 
                },
                fontSize,
                0.0f,
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
