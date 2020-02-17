echo 1. > result_007.txt
DagInterpreter.exe "-help" "-sca" >> result_007.txt

echo. >> result_007.txt
echo 2. >> result_007.txt
DagInterpreter.exe "sca" >> result_007.txt

echo. >> result_007.txt
echo 3. >> result_007.txt
DagInterpreter.exe "--sca" >> result_007.txt

echo. >> result_007.txt
echo 4. >> result_007.txt
DagInterpreter.exe "-sca-" >> result_007.txt

echo. >> result_007.txt
echo 5. >> result_007.txt
DagInterpreter.exe "-sca" "-sca" >> result_007.txt

echo. >> result_007.txt
echo 6. >> result_007.txt
DagInterpreter.exe "-sca" "--sca" >> result_007.txt

echo. >> result_007.txt
echo 7. >> result_007.txt
DagInterpreter.exe "-sca" "-sca" "--sca" >> result_007.txt

echo. >> result_007.txt
echo 8. >> result_007.txt
DagInterpreter.exe "-sca" "-sca-" >> result_007.txt

echo. >> result_007.txt
echo 9. >> result_007.txt
DagInterpreter.exe "-sca" "-sca" "-sca-" >> result_007.txt

echo. >> result_007.txt
echo 10. >> result_007.txt
DagInterpreter.exe "-sca" >> result_007.txt

:main
fc .\result_007.txt .\pattern_007.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_007.err

:left
exit