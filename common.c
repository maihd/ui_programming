#include "common.h"
#include <assert.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void* Memory_Reserve(size_t size)
{
    return VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_READWRITE);
}

void* Memory_Commit(void* block, size_t size)
{
    return VirtualAlloc(block, size, MEM_COMMIT, PAGE_READWRITE);
}

bool Memory_Decommit(void* block, size_t size)
{
    return (bool)VirtualFree(block, size, MEM_DECOMMIT);
}

bool Memory_Release(void* block)
{
    return (bool)VirtualFree(block, 0, MEM_RELEASE);
}

Arena* Arena_Create(int32_t committed, int32_t reserved)
{
    assert(ARENA_DEFAULT_HEAD_POSITION < committed && committed <= reserved);

    void* block = Memory_Reserve(reserved);
    void* committedBlock = Memory_Commit(block, committed);
    assert(block != NULL);
    assert(block == committedBlock);

    Arena* arena = (Arena*)block;
    
    arena->prev         = NULL;
    arena->current      = arena;

    arena->origin       = 0;
    arena->position     = ARENA_DEFAULT_HEAD_POSITION;
    arena->capacity     = reserved;

    arena->committed    = committed;
    arena->alignment    = 16;

    return arena;
}

Arena* Arena_CreateDefault(void)
{
    return Arena_Create(ARENA_DEFAULT_SIZE_COMMITED, ARENA_DEFAULT_SIZE_RESERVED);
}

void Arena_Destroy(Arena* arena)
{
    if (arena)
    {
        Arena* destroyingArena = arena->current;
        while (destroyingArena)
        {
            Arena* prevArena = destroyingArena->prev;
            Memory_Release(destroyingArena);
            destroyingArena = prevArena;
        }   
    }
}

void* Arena_Acquire(Arena* arena, int32_t size)
{
    Arena* current = arena->current;
    int32_t newPosition = current->position + size;

    if (newPosition > current->capacity)
    {
        Arena* newArena = Arena_CreateDefault();
        newArena->prev = current;
        newArena->origin = current->origin + current->capacity;
        
        newPosition = newArena->position + size;
        current = newArena;
    }

    if (newPosition >= current->committed)
    {
        current->committed *= 2;
        if (current->committed > current->capacity)
        {
            current->committed = current->capacity;
        }

        Memory_Commit(arena, current->committed);
    }

    void* result = (uint8_t*)current + current->position;
    current->position = newPosition;
    return result;
}

void Arena_Collect(Arena* arena, void* ptr)
{
    (void)arena;
    (void)ptr;
}

void Arena_SetAlignment(Arena* arena, int32_t alignment)
{
    assert(arena != NULL);
    arena->current->alignment = alignment;
}

void Arena_SetPosition(Arena* arena, int32_t position)
{
    assert(arena != NULL);
    assert(position >= ARENA_DEFAULT_HEAD_POSITION && position <= arena->current->capacity);
    arena->current->position = position;
}

void Arena_Clear(Arena* arena)
{
    assert(arena != NULL);
    arena->current->position = ARENA_DEFAULT_HEAD_POSITION;
}

Arena* Arena_GetScratch(void)
{
    static __thread Arena* scratch = NULL;
    if (scratch == NULL)
    {
        scratch = Arena_CreateDefault();
    } 

    return scratch;
}
