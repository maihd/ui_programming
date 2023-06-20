@echo off

set CFLAGS=-O3 -fno-sanitize=undefined -Iinclude
set LFLAGS=lib/raylibdll.lib common.lib
set SOURCE=lib.c ui.c

zig cc -shared -o lib.dll -fPIC %SOURCE% %CFLAGS% %LFLAGS%