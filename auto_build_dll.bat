@echo off

set CFLAGS=-fno-sanitize=undefined -Iinclude
set LFLAGS=

zig cc -o auto_build_dll.exe src/auto_build_dll.c src/HotDylibEx.c -fno-sanitize=undefined

auto_build_dll.exe