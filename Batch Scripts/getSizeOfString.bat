@echo off
rem This batch gives you the length of a string

goto starter

:doagain
cls

:starter
setlocal
set /p mystring="Write string to continue: "
call :strlen result mystring
echo Length: %result%
goto repeater

:strlen
(   
    setlocal EnableDelayedExpansion
    set "s=!%~2!#"
    set "len=0"
    for %%P in (4096 2048 1024 512 256 128 64 32 16 8 4 2 1) do (
        if "!s:~%%P,1!" neq "" ( 
            set /a "len+=%%P"
            set "s=!s:~%%P!"
        )
    )
)
( 
    endlocal
    set "%~1=%len%"
    exit /b
)

:repeater
set /p choice="Do you want to check another string (y/n)?: "
if "%choice%" == "y" goto doagain
if "%choice%" == "n" goto eof
cls
goto repeater