@echo off
setlocal enabledelayedexpansion

set "command=C:\Program Files\LLVM\bin\clang-format.exe"

set "files=app\src\*.cpp app\lib\*.h server\*.cpp server\*.h"

!command! -i %files%

echo Code formatting completed!
