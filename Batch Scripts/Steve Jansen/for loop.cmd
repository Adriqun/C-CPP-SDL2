@echo off

rem looping through files
FOR %%I IN (%USERPROFILE%\*) DO ECHO %%I

rem looping through dirs
for /d %%i in (%userprofile%\*) do @echo dirs: %%i

rem recursively loop through files in all subfolders of the %temp% folder
set temp="C:"
for /r "%temp%" %%i in (*) do echo subfiles: %%i

rem recursively loop through all subfolders in the %temp% folder
for /r "%temp%" /d %%i in (*) do echo subfolders: %%i