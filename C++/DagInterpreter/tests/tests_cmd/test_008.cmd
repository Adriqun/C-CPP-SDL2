echo 1. > result_008.txt
DagInterpreter.exe "-help" "-pnn" >> result_008.txt

echo. >> result_008.txt
echo 2. >> result_008.txt
DagInterpreter.exe "pnn" >> result_008.txt

echo. >> result_008.txt
echo 3. >> result_008.txt
DagInterpreter.exe "--pnn" >> result_008.txt

echo. >> result_008.txt
echo 4. >> result_008.txt
DagInterpreter.exe "-pnn-" >> result_008.txt

echo. >> result_008.txt
echo 5. >> result_008.txt
DagInterpreter.exe "-pnn" "-pnn" >> result_008.txt

echo. >> result_008.txt
echo 6. >> result_008.txt
DagInterpreter.exe "-pnn" "--pnn" >> result_008.txt

echo. >> result_008.txt
echo 7. >> result_008.txt
DagInterpreter.exe "-pnn" "-pnn" "--pnn" >> result_008.txt

echo. >> result_008.txt
echo 8. >> result_008.txt
DagInterpreter.exe "-pnn" "-pnn-" >> result_008.txt

echo. >> result_008.txt
echo 9. >> result_008.txt
DagInterpreter.exe "-pnn" "-pnn" "-pnn-" >> result_008.txt

echo. >> result_008.txt
echo 10. >> result_008.txt
DagInterpreter.exe "-pnn" >> result_008.txt

:main
fc .\result_008.txt .\pattern_008.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_008.err

:left
exit