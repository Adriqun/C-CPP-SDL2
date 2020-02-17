echo 1. > result_011.txt
DagInterpreter.exe "-help" "-rmc" "-rdc" "0" >> result_011.txt

echo. >> result_011.txt
echo 2. >> result_011.txt
DagInterpreter.exe "-help" "-rdc" "0" "-rmc" >> result_011.txt

echo. >> result_011.txt
echo 3. >> result_011.txt
DagInterpreter.exe "-rmc" "-rdc" "0" >> result_011.txt

echo. >> result_011.txt
echo 4. >> result_011.txt
DagInterpreter.exe "-rdc" "0" "-rmc" >> result_011.txt

echo. >> result_011.txt
echo 5. >> result_011.txt
DagInterpreter.exe "-rmc" "-rdc" "1" >> result_011.txt

echo. >> result_011.txt
echo 6. >> result_011.txt
DagInterpreter.exe "-rdc" "1" "-rmc" >> result_011.txt

:main
fc .\result_011.txt .\pattern_011.pat
if %errorlevel% equ 0 goto left

:error
copy nul error_011.err

:left
exit