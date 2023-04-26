@echo off
call setEnv.bat
"E:\SOFTWARE\DARK TECH\MathWorks\toolbox\shared\coder\ninja\win64\ninja.exe" -t compdb cc cxx cudac > compile_commands.json
"E:\SOFTWARE\DARK TECH\MathWorks\toolbox\shared\coder\ninja\win64\ninja.exe" -v %*
