@echo off

goto starter

:doagain
cls

:starter
setlocal
set /p sequence="Write text to continue: "
set /a result=0
goto saving

:saving
set char=%sequence:~0,1%
set sequence=%sequence:~1%
set /a result=%result%+1
md (%result%)%char%
if not "%sequence%" == "%strterm%" goto saving


:repeater
set /p choice="Do you want to try again (y/n)?: "
if "%choice%" == "y" goto doagain
if "%choice%" == "n" goto eof
cls
goto repeater