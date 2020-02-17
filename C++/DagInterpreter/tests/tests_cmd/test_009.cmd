echo 1. > result_009.txt
DagInterpreter.exe "-help" "-top" "0" >> result_009.txt

echo. >> result_009.txt
echo 2. >> result_009.txt
DagInterpreter.exe "-help" "-top" >> result_009.txt

echo. >> result_009.txt
echo 3. >> result_009.txt
DagInterpreter.exe "top" >> result_009.txt

echo. >> result_009.txt
echo 4. >> result_009.txt
DagInterpreter.exe "--top" >> result_009.txt

echo. >> result_009.txt
echo 5. >> result_009.txt
DagInterpreter.exe "-top-" >> result_009.txt

echo. >> result_009.txt
echo 6. >> result_009.txt
DagInterpreter.exe "-top" "-top" >> result_009.txt

echo. >> result_009.txt
echo 7. >> result_009.txt
DagInterpreter.exe "-top" "--top" >> result_009.txt

echo. >> result_009.txt
echo 8. >> result_009.txt
DagInterpreter.exe "-top" "-top" "--top" >> result_009.txt

echo. >> result_009.txt
echo 9. >> result_009.txt
DagInterpreter.exe "-top" "-top-" >> result_009.txt

echo. >> result_009.txt
echo 10. >> result_009.txt
DagInterpreter.exe "-top" "-top" "-top-" >> result_009.txt

echo. >> result_009.txt
echo 11. >> result_009.txt
DagInterpreter.exe "-top" "-1" >> result_009.txt

echo. >> result_009.txt
echo 12. >> result_009.txt
DagInterpreter.exe "-top" "-100000000" >> result_009.txt

echo. >> result_009.txt
echo 13. >> result_009.txt
DagInterpreter.exe "-top" "999999999999999999999999" >> result_009.txt

echo. >> result_009.txt
echo 14. >> result_009.txt
DagInterpreter.exe "-top" "123a123" >> result_009.txt

echo. >> result_009.txt
echo 15. >> result_009.txt
DagInterpreter.exe "-top" "1234567890b" >> result_009.txt

echo. >> result_009.txt
echo 16. >> result_009.txt
DagInterpreter.exe "-top" "123" >> result_009.txt

echo. >> result_009.txt
echo 17. >> result_009.txt
DagInterpreter.exe "-top" "123" "-top" "123" >> result_009.txt

:main
fc .\result_009.txt .\pattern_009.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_009.err

:left
exit