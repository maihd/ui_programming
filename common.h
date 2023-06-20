#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef COMMON_API
#define COMMON_API __declspec(dllimport)
#endif

// --------------------------------------------------
// Memory Arena
// --------------------------------------------------

#define ARENA_DEFAULT_HEAD_POSITION (64)
#define ARENA_DEFAULT_SIZE_COMMITED (64 << 10)
#define ARENA_DEFAULT_SIZE_RESERVED (64 << 20)

typedef struct Arena Arena;
struct Arena
{
    Arena*  prev;
    Arena*  current;
    
    int32_t origin;
    int32_t position;
    int32_t capacity;
    int32_t committed;
    int32_t alignment;
};

COMMON_API Arena*   Arena_Create(int32_t committed, int32_t reserved);
COMMON_API Arena*   Arena_CreateDefault(void);
COMMON_API void     Arena_Destroy(Arena* arena);

COMMON_API void*    Arena_Acquire(Arena* arena, int32_t size);
COMMON_API void     Arena_Collect(Arena* arena, void* ptr);

COMMON_API void     Arena_SetAlignment(Arena* arena, int32_t alignment);
COMMON_API void     Arena_SetPosition(Arena* arena, int32_t position);
COMMON_API void     Arena_Clear(Arena* arena);

// --------------------------------------------------
// Utils
// --------------------------------------------------

COMMON_API Arena*   Arena_GetScratch(void);
