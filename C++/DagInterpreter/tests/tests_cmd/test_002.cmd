echo 1. > result_002.txt
DagInterpreter.exe "-help" "-rma" >> result_002.txt

echo. >> result_002.txt
echo 2. >> result_002.txt
DagInterpreter.exe "rma" >> result_002.txt

echo. >> result_002.txt
echo 3. >> result_002.txt
DagInterpreter.exe "--rma" >> result_002.txt

echo. >> result_002.txt
echo 4. >> result_002.txt
DagInterpreter.exe "-rma-" >> result_002.txt

echo. >> result_002.txt
echo 5. >> result_002.txt
DagInterpreter.exe "-rma" "-rma" >> result_002.txt

echo. >> result_002.txt
echo 6. >> result_002.txt
DagInterpreter.exe "-rma" "--rma" >> result_002.txt

echo. >> result_002.txt
echo 7. >> result_002.txt
DagInterpreter.exe "-rma" "-rma" "--rma" >> result_002.txt

echo. >> result_002.txt
echo 8. >> result_002.txt
DagInterpreter.exe "-rma" "-rma-" >> result_002.txt

echo. >> result_002.txt
echo 9. >> result_002.txt
DagInterpreter.exe "-rma" "-rma" "-rma-" >> result_002.txt

echo. >> result_002.txt
echo 10. >> result_002.txt
DagInterpreter.exe "-rma" >> result_002.txt

:main
fc .\result_002.txt .\pattern_002.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_002.err

:left
exit