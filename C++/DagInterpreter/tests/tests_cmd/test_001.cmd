echo 1. > result_001.txt
DagInterpreter.exe "-help" "-rmc" >> result_001.txt

echo. >> result_001.txt
echo 2. >> result_001.txt
DagInterpreter.exe "rmc" >> result_001.txt

echo. >> result_001.txt
echo 3. >> result_001.txt
DagInterpreter.exe "--rmc" >> result_001.txt

echo. >> result_001.txt
echo 4. >> result_001.txt
DagInterpreter.exe "-rmc-" >> result_001.txt

echo. >> result_001.txt
echo 5. >> result_001.txt
DagInterpreter.exe "-rmc" "-rmc" >> result_001.txt

echo. >> result_001.txt
echo 6. >> result_001.txt
DagInterpreter.exe "-rmc" "--rmc" >> result_001.txt

echo. >> result_001.txt
echo 7. >> result_001.txt
DagInterpreter.exe "-rmc" "-rmc" "--rmc" >> result_001.txt

echo. >> result_001.txt
echo 8. >> result_001.txt
DagInterpreter.exe "-rmc" "-rmc-" >> result_001.txt

echo. >> result_001.txt
echo 9. >> result_001.txt
DagInterpreter.exe "-rmc" "-rmc" "-rmc-" >> result_001.txt

echo. >> result_001.txt
echo 10. >> result_001.txt
DagInterpreter.exe "-rmc" >> result_001.txt

:main
fc .\result_001.txt .\pattern_001.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_001.err

:left
exit