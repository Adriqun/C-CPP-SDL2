@echo off
rem This batch file loop through string like: input:"Name" -> In order 'N' 'a' 'm' 'e' 12.07.2018 Adrian Michalek


cls
echo.
echo -----------------LOOP THROUGH STRING - IN BATCH-----------------
echo.
set /p sequence="Write string to continue: "

goto loop

rem REPEATER
:doagain
cls
set /p sequence="Write string to continue: "

rem LOOP STRING
:loop

:: get first character from input
set char=%sequence:~0,1%

:: remove first character from input
set sequence=%sequence:~1%

:: do something with %char%, e.g. simply print it out
echo char: %char%

:: repeat until only the string terminator is left
if not "%sequence%" == "%strterm%" goto loop

set /p choice="Do you want to test another string (y/n)? "
if "%choice%" == "y" goto doagain
if "%choice%" == "n" goto end

:end
exit