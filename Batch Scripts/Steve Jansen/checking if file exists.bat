@echo off

set filename=%1

if not exist "%filename%" (
	echo Cannot find "%filename%"
) else (
	echo OK
)