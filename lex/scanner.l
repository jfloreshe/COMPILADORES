%{
#include "scanner.h"
%}

%%
"int" return INT;
"else" return ELSE;
"for" return FOR;
"while" return WHILE;
"switch" return SWITCH;
"case" return CASE;
"break" return BREAK;
"continue" return CONTINUE;

,			return COMA;
;			return PUNTOYCOMA;
\+			return OPERADORMAS;
\(			return LEFTPARENTESIS;
\)			return RIGHTPARENTESIS;
"{"			return LEFTLLAVE;
"}"			return RIGHTLLAVE;
"["			return LEFTCORCHETE;
"]"			return RIGHTCORCHETE;
- 				return OPERADORMENOS;
[a-zA-Z][a-zA-Z0-9_]* return IDENTIFICADOR;
[-]?[0-9][0-9]* return NUMERO;
[ \t\n]		;
.				printf("undefined\n");

%%

int yywrap(){
	return 1;
}
