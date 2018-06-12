@echo OFF
rem stderr
dir blah.txt 2>> error.txt

rem combination of stdout and stderr
dir blah.txt > error2.txt 2>&1