REM creates and overwrite
DIR > output.txt

SET /A myvariable=5+100
REM append to existing file or only create file if not exists (DOESNT WORK - don't know why)
@echo %myvariable% >> output2.txt

rem Solution if we have @ECHO OFF
@echo OFF
>output3.txt echo %myvariable%
@echo %myvariable% >> output4.txt
