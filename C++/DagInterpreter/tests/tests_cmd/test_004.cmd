echo 1. > result_004.txt
DagInterpreter.exe "-help" "-rda" "0" >> result_004.txt

echo. >> result_004.txt
echo 2. >> result_004.txt
DagInterpreter.exe "-help" "-rda" >> result_004.txt

echo. >> result_004.txt
echo 3. >> result_004.txt
DagInterpreter.exe "rda" >> result_004.txt

echo. >> result_004.txt
echo 4. >> result_004.txt
DagInterpreter.exe "--rda" >> result_004.txt

echo. >> result_004.txt
echo 5. >> result_004.txt
DagInterpreter.exe "-rda-" >> result_004.txt

echo. >> result_004.txt
echo 6. >> result_004.txt
DagInterpreter.exe "-rda" "-rda" >> result_004.txt

echo. >> result_004.txt
echo 7. >> result_004.txt
DagInterpreter.exe "-rda" "--rda" >> result_004.txt

echo. >> result_004.txt
echo 8. >> result_004.txt
DagInterpreter.exe "-rda" "-rda" "--rda" >> result_004.txt

echo. >> result_004.txt
echo 9. >> result_004.txt
DagInterpreter.exe "-rda" "-rda-" >> result_004.txt

echo. >> result_004.txt
echo 10. >> result_004.txt
DagInterpreter.exe "-rda" "-rda" "-rda-" >> result_004.txt

echo. >> result_004.txt
echo 11. >> result_004.txt
DagInterpreter.exe "-rda" "-1" >> result_004.txt

echo. >> result_004.txt
echo 12. >> result_004.txt
DagInterpreter.exe "-rda" "-100000000" >> result_004.txt

echo. >> result_004.txt
echo 13. >> result_004.txt
DagInterpreter.exe "-rda" "999999999999999999999999" >> result_004.txt

echo. >> result_004.txt
echo 14. >> result_004.txt
DagInterpreter.exe "-rda" "123a123" >> result_004.txt

echo. >> result_004.txt
echo 15. >> result_004.txt
DagInterpreter.exe "-rda" "1234567890b" >> result_004.txt

echo. >> result_004.txt
echo 16. >> result_004.txt
DagInterpreter.exe "-rda" "123" >> result_004.txt

echo. >> result_004.txt
echo 17. >> result_004.txt
DagInterpreter.exe "-rda" "123" "-rda" "123" >> result_004.txt

:main
fc .\result_004.txt .\pattern_004.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_004.err

:left
exit