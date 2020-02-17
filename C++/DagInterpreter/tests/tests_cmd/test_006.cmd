echo 1. > result_006.txt
DagInterpreter.exe "-help" "-sra" >> result_006.txt

echo. >> result_006.txt
echo 2. >> result_006.txt
DagInterpreter.exe "sra" >> result_006.txt

echo. >> result_006.txt
echo 3. >> result_006.txt
DagInterpreter.exe "--sra" >> result_006.txt

echo. >> result_006.txt
echo 4. >> result_006.txt
DagInterpreter.exe "-sra-" >> result_006.txt

echo. >> result_006.txt
echo 5. >> result_006.txt
DagInterpreter.exe "-sra" "-sra" >> result_006.txt

echo. >> result_006.txt
echo 6. >> result_006.txt
DagInterpreter.exe "-sra" "--sra" >> result_006.txt

echo. >> result_006.txt
echo 7. >> result_006.txt
DagInterpreter.exe "-sra" "-sra" "--sra" >> result_006.txt

echo. >> result_006.txt
echo 8. >> result_006.txt
DagInterpreter.exe "-sra" "-sra-" >> result_006.txt

echo. >> result_006.txt
echo 9. >> result_006.txt
DagInterpreter.exe "-sra" "-sra" "-sra-" >> result_006.txt

echo. >> result_006.txt
echo 10. >> result_006.txt
DagInterpreter.exe "-sra" >> result_006.txt

:main
fc .\result_006.txt .\pattern_006.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_006.err

:left
exit