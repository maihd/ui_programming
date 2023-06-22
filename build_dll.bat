@echo off

set CFLAGS=-O3 -fno-sanitize=undefined -Iinclude
set LFLAGS=lib/raylibdll.lib common.lib
set SOURCE=src/lib.c src/ui.c

zig cc -shared -o lib.dll %SOURCE% %CFLAGS% %LFLAGS%