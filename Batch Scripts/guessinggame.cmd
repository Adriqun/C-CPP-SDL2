@echo off
color 0e
title Guessing Game
set /a guessnum=0
set /a guess=%RANDOM%%%100+1

echo -------------------------------------------------
echo Welcome to the Guessing Game!
echo.
echo Think about a number between 1...100!
echo I would try to answer but You have to help me by saying 'lesser' or 'greater' then 'yes' if I guessed.
echo -------------------------------------------------
echo.

:top
echo.
echo Number is %guess%
set answer=
echo.

if "%answer%"=="lower" (
	set /a guess/=2
)
if "%answer%"=="greater" (
	set /a guess+=((100-%guess%)/2)
)
if "%answer%"=="yes" (
	goto equal
)

set /a guessnum=%guessnum% +1
goto top

:equal
echo Daah I knew I would win.
echo.
echo It took me %guessnum% guesses.
echo.
pause