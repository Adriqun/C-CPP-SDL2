@echo off

set my_var=%1
set ERRORLEVEL=0

if "%my_var%"=="" (
	echo Variable is empty.
	set ERRORLEVEL=1
)

if not defined my_var (
	echo Variable is not defined.
	set ERRORLEVEL=1
)

rem insensitive comparison, do not pay attention on letter size
if "%my_var%"=="sth" (
	echo Variable is equil to "sth".
)



set /a var=1
if /i "%var%" equ "1" echo Value is 1
if /i "%var%" equ "0" echo Value is not 0
if /i "$var%" geq "1" echo Value is greater than or equil to 1
if /i "%var%" leq "1" echo Value is less than or equil to 1

rem checking a return code
if /i "%ERRORLEVEL%" neq "0" (
	echo Execution failed.
)