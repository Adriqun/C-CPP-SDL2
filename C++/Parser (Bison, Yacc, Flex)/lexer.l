/*----- Prolog section -----*/
%option noyywrap

%{
	#include <iostream>
	#include <cmath>
	#pragma warning (disable: 4005)
	#include "parser.h"
%}

NUMBER ([0-9]+)|([0-9]*\.[0-9]+)


%%	/*----- Definition section -----*/


{NUMBER}	{yylval = atof(yytext); return NUM;}
[+*/()-]	{return yytext[0];}
[\n]		{return '\n';}
[ \t]		{/*empty*/}
"quit"		{yyterminate();}
.			/*empty*/

%%	/*----- User code section -----*/
