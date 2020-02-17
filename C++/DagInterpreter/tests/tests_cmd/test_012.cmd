echo 1. > result_012.txt
DagInterpreter.exe "-help" "-sla" "-sra" "-sca" >> result_012.txt

echo. >> result_012.txt
echo 2. >> result_012.txt
DagInterpreter.exe "-help" "-sla" "-sca" "-sra" >> result_012.txt

echo. >> result_012.txt
echo 3. >> result_012.txt
DagInterpreter.exe "-help" "-sra" "-sla" "-sca" >> result_012.txt

echo. >> result_012.txt
echo 4. >> result_012.txt
DagInterpreter.exe "-help" "-sra" "-sca" "-sla" >> result_012.txt

echo. >> result_012.txt
echo 5. >> result_012.txt
DagInterpreter.exe "-help" "-sca" "-sla" "-sra" >> result_012.txt

echo. >> result_012.txt
echo 6. >> result_012.txt
DagInterpreter.exe "-help" "-sca" "-sra" "-sla" >> result_012.txt

echo 7. >> result_012.txt
DagInterpreter.exe "-sla" "-sra" "-sca" >> result_012.txt

echo. >> result_012.txt
echo 8. >> result_012.txt
DagInterpreter.exe "-sla" "-sca" "-sra" >> result_012.txt

echo. >> result_012.txt
echo 9. >> result_012.txt
DagInterpreter.exe "-sra" "-sla" "-sca" >> result_012.txt

echo. >> result_012.txt
echo 10. >> result_012.txt
DagInterpreter.exe "-sra" "-sca" "-sla" >> result_012.txt

echo. >> result_012.txt
echo 11. >> result_012.txt
DagInterpreter.exe "-sca" "-sla" "-sra" >> result_012.txt

echo. >> result_012.txt
echo 12. >> result_012.txt
DagInterpreter.exe "-sca" "-sra" "-sla" >> result_012.txt

:main
fc .\result_012.txt .\pattern_012.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_012.err

:left
exit