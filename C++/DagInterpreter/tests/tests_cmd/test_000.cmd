echo 1. > result_000.txt
DagInterpreter.exe >> result_000.txt

echo. >> result_000.txt
echo 2. >> result_000.txt
DagInterpreter.exe "help" >> result_000.txt

echo. >> result_000.txt
echo 3. >> result_000.txt
DagInterpreter.exe "--help" >> result_000.txt

echo. >> result_000.txt
echo 4. >> result_000.txt
DagInterpreter.exe "-help-" >> result_000.txt

echo. >> result_000.txt
echo 5. >> result_000.txt
DagInterpreter.exe "-help" "-help" >> result_000.txt

echo. >> result_000.txt
echo 6. >> result_000.txt
DagInterpreter.exe "-help" "--help" >> result_000.txt

echo. >> result_000.txt
echo 7. >> result_000.txt
DagInterpreter.exe "-help" "-help" "--help" >> result_000.txt

echo. >> result_000.txt
echo 8. >> result_000.txt
DagInterpreter.exe "-help" "-help-" >> result_000.txt

echo. >> result_000.txt
echo 9. >> result_000.txt
DagInterpreter.exe "-help" "-help" "-help-" >> result_000.txt

echo. >> result_000.txt
echo 10. >> result_000.txt
DagInterpreter.exe "-help" >> result_000.txt

:main
fc .\result_000.txt .\pattern_000.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_000.err

:left
exit