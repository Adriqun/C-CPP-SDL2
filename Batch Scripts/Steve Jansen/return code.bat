@ECHO OFF

REM %ERRORLEVEL% sets every next if, echo, set etc.
if %ERRORLEVEL% neq 0
(
	echo blah blah
)
else
(
	echo blah2 blah2
)

rem This is true whenever errorlevel is equil or greater than 1
if ERRORLEVEL 1
(
	echo blah3
)


rem 9009 is special code, shows if script is in your path
rem somefile.exe
rem if %ERRORLEVEL% equ 9009
rem (
rem rem sth
rem )

rem && if sth.exe succeeded and || if not
sth.exe && echo sth.exe succeeded!
sth.exe || echo sth.exe failed!
rem sth.exe || EXIT /B 1 <-exit script and returns 1
rem sth.exe || GOTO :EOF <- goes to the end of file and returns 1 auto.

rem It's good to set const variables at the top of your script like:
SET /A ERROR_HELP_SCREEN=1
SET /A ERROR_FILE_NOT_FOUND=2
SET /A ERROR_FILE_READ_ONLY=4
SET /A ERROR_UNKNOWN=8

