@echo off

set CFLAGS=-O3 -fno-sanitize=undefined -Iinclude -DCOMMON_API=__declspec(dllexport)
set LFLAGS=-L.
set SOURCE=src/common.c

zig cc -shared -o common.dll %SOURCE% %CFLAGS% %LFLAGS%