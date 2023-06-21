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
            DrawRectangleRec(command.rect, WHITE);
        }
    }
}

bool UIButton(UIContext* context, const char* text)
{
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
            .rect = {
                .x = 100,
                .y = 100,
                .width = 200,
                .height = 60
            }
        };
    }

    return false;
}
