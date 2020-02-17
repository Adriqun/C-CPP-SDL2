echo 1. > result_010.txt
DagInterpreter.exe "-help" "-rma" "-rda" "0" >> result_010.txt

echo. >> result_010.txt
echo 2. >> result_010.txt
DagInterpreter.exe "-help" "-rda" "0" "-rma" >> result_010.txt

echo. >> result_010.txt
echo 3. >> result_010.txt
DagInterpreter.exe "-rma" "-rda" "0" >> result_010.txt

echo. >> result_010.txt
echo 4. >> result_010.txt
DagInterpreter.exe "-rda" "0" "-rma" >> result_010.txt

echo. >> result_010.txt
echo 5. >> result_010.txt
DagInterpreter.exe "-rma" "-rda" "1" >> result_010.txt

echo. >> result_010.txt
echo 6. >> result_010.txt
DagInterpreter.exe "-rda" "1" "-rma" >> result_010.txt

:main
fc .\result_010.txt .\pattern_010.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_010.err

:left
exit