@echo off

set CFLAGS=-O3 -fno-sanitize=undefined -Iinclude
set LFLAGS=lib/raylibdll.lib common.lib

zig cc src/main.c src/HotDylib.c %CFLAGS% %LFLAGS%