@echo off

call config.bat

set CFLAGS=-O3 -fno-sanitize=undefined -Iinclude
set LFLAGS=lib/raylibdll.lib common.lib
set SOURCE=src/lib.c src/ui.c

%CC% -shared -o lib.dll %SOURCE% %CFLAGS% %LFLAGS%