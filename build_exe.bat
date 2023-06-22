@echo off

call config.bat

set CFLAGS=-O3 -fno-sanitize=undefined -Iinclude -DHOTDYLIB_PDB_UNLOCK=0
set LFLAGS=lib/raylibdll.lib common.lib

%CC% src/main.c src/HotDylib.c %CFLAGS% %LFLAGS%