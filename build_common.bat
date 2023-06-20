@echo off

set CFLAGS=-O3 -fno-sanitize=undefined -Iinclude -DCOMMON_API=__declspec(dllexport)
set LFLAGS=-L.

zig cc -shared -o common.dll common.c %CFLAGS% %LFLAGS%