echo 1. > result_005.txt
DagInterpreter.exe "-help" "-sla" >> result_005.txt

echo. >> result_005.txt
echo 2. >> result_005.txt
DagInterpreter.exe "sla" >> result_005.txt

echo. >> result_005.txt
echo 3. >> result_005.txt
DagInterpreter.exe "--sla" >> result_005.txt

echo. >> result_005.txt
echo 4. >> result_005.txt
DagInterpreter.exe "-sla-" >> result_005.txt

echo. >> result_005.txt
echo 5. >> result_005.txt
DagInterpreter.exe "-sla" "-sla" >> result_005.txt

echo. >> result_005.txt
echo 6. >> result_005.txt
DagInterpreter.exe "-sla" "--sla" >> result_005.txt

echo. >> result_005.txt
echo 7. >> result_005.txt
DagInterpreter.exe "-sla" "-sla" "--sla" >> result_005.txt

echo. >> result_005.txt
echo 8. >> result_005.txt
DagInterpreter.exe "-sla" "-sla-" >> result_005.txt

echo. >> result_005.txt
echo 9. >> result_005.txt
DagInterpreter.exe "-sla" "-sla" "-sla-" >> result_005.txt

echo. >> result_005.txt
echo 10. >> result_005.txt
DagInterpreter.exe "-sla" >> result_005.txt

:main
fc .\result_005.txt .\pattern_005.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_005.err

:left
exit