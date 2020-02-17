echo 1. > result_003.txt
DagInterpreter.exe "-help" "-rdc" "0" >> result_003.txt

echo. >> result_003.txt
echo 2. >> result_003.txt
DagInterpreter.exe "-help" "-rdc" >> result_003.txt

echo. >> result_003.txt
echo 3. >> result_003.txt
DagInterpreter.exe "rdc" >> result_003.txt

echo. >> result_003.txt
echo 4. >> result_003.txt
DagInterpreter.exe "--rdc" >> result_003.txt

echo. >> result_003.txt
echo 5. >> result_003.txt
DagInterpreter.exe "-rdc-" >> result_003.txt

echo. >> result_003.txt
echo 6. >> result_003.txt
DagInterpreter.exe "-rdc" "-rdc" >> result_003.txt

echo. >> result_003.txt
echo 7. >> result_003.txt
DagInterpreter.exe "-rdc" "--rdc" >> result_003.txt

echo. >> result_003.txt
echo 8. >> result_003.txt
DagInterpreter.exe "-rdc" "-rdc" "--rdc" >> result_003.txt

echo. >> result_003.txt
echo 9. >> result_003.txt
DagInterpreter.exe "-rdc" "-rdc-" >> result_003.txt

echo. >> result_003.txt
echo 10. >> result_003.txt
DagInterpreter.exe "-rdc" "-rdc" "-rdc-" >> result_003.txt

echo. >> result_003.txt
echo 11. >> result_003.txt
DagInterpreter.exe "-rdc" "-1" >> result_003.txt

echo. >> result_003.txt
echo 12. >> result_003.txt
DagInterpreter.exe "-rdc" "-100000000" >> result_003.txt

echo. >> result_003.txt
echo 13. >> result_003.txt
DagInterpreter.exe "-rdc" "999999999999999999999999" >> result_003.txt

echo. >> result_003.txt
echo 14. >> result_003.txt
DagInterpreter.exe "-rdc" "123a123" >> result_003.txt

echo. >> result_003.txt
echo 15. >> result_003.txt
DagInterpreter.exe "-rdc" "1234567890b" >> result_003.txt

echo. >> result_003.txt
echo 16. >> result_003.txt
DagInterpreter.exe "-rdc" "123" >> result_003.txt

echo. >> result_003.txt
echo 17. >> result_003.txt
DagInterpreter.exe "-rdc" "123" "-rdc" "123" >> result_003.txt

:main
fc .\result_003.txt .\pattern_003.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_003.err

:left
exit