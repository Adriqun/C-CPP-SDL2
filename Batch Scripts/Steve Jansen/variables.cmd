@ECHO OFF
SET foo="bar"
SET /A foo2=3
SET foo3=sth

REM To be sure that value is numerical /A
SET /A four=2+2

REM Do not try to overwrite this global variables like: SET temp=sth
echo %TEMP%
echo %DATE%
echo %RANDOM%
echo %CD%

REM reading value
echo %foo%
echo %four%

rem Special space in memory
SETLOCAL
SET localthing="brrr"
echo %localthing%
ENDLOCAL

rem Prints name of this file.
echo %0


rem It's very useful to write those commands below in every batch file
rem SETLOCAL ENABLEEXTENSIONS
rem SET me=%~n0
rem SET parent=%~dp0

rem ~d drive
echo ~d means:%~d0

rem ~p path
echo ~p means:%~p0

rem ~n file name
echo ~n means:%~n0

rem ~dp combined drive + path
echo ~dp means:%~dp0

REM ~t timestamp, ~z size

REM ~nx file name + extension
echo ~nx means:%~nx0

rem ~f full path
echo ~f means:%~f0

REM ~s shorts the path
echo ~fs means:%~fs0