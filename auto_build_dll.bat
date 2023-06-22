@echo off

call config.bat

set CFLAGS=-fno-sanitize=undefined -Iinclude
set LFLAGS=

%CC% -o auto_build_dll.exe src/auto_build_dll.c src/HotDylibEx.c -fno-sanitize=undefined

auto_build_dll.exe