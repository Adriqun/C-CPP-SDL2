@echo off
rem Execute cmd n times - test reasons - 05.11.2018 Adrian Michalek

set /a NUM_OF_TESTS=31
set /a number=1

rem REPEATER
:loop
	set /a num=0
	:inter
		set /a num=%num%+1
		rem execute
		call temp.exe %number%
	if %num% LSS 10 (goto inter)
	set /a number=%number%+1
if %number% LSS %NUM_OF_TESTS% (goto loop)

:end
exit