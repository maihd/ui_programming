#pragma once

#include <stdint.h>

#ifndef COMMON_API
#define COMMON_API __declspec(dllimport)
#endif

typedef struct Arena Arena;
struct Arena
{
    Arena*  prev;
    Arena*  current;
    
    int32_t position;
    int32_t capacity;
    int32_t committed;
    int32_t alignment;
};

COMMON_API Arena*   Arena_Create(void);
COMMON_API Arena*   Arena_Create2(int32_t committed, int32_t reserved);
COMMON_API void     Arena_Destroy(Arena* arena);

COMMON_API void*    Arena_Acquire(Arena* arena, int32_t size);
COMMON_API void     Arena_Collect(Arena* arena, void* ptr);

COMMON_API void     Arena_SetAlignment(Arena* arena, int32_t alignment);
COMMON_API void     Arena_SetPosition(Arena* arena, int32_t position);
COMMON_API void     Arena_Clear(Arena* arena);
