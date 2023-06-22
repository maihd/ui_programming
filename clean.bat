@echo off

del a.exe /F /Q
del a.pdb /F /Q

del lib.dll /F /Q
del lib.lib /F /Q
del lib.pdb /F /Q
del lib.exp /F /Q
del lib.dll.* /F /Q

del common.dll /F /Q
del common.lib /F /Q
del common.pdb /F /Q
del common.exp /F /Q

del auto_build_dll.exe /F /Q
del auto_build_dll.pdb /F /Q