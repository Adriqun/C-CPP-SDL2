@echo off
setlocal

:: script global variables
set me=%~n0
set log=%TEMP%\%me%.txt

:: do sth cool, then log it
call :tee "%me%": Hello, world!

sim/h/stlext/