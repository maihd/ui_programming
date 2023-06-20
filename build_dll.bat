@echo off

set CFLAGS=-O3 -fno-sanitize=undefined -Iinclude
set LFLAGS=lib/raylibdll.lib common.lib

zig cc -shared -o lib.dll -fPIC lib.c %CFLAGS% %LFLAGS%