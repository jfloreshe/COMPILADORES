#include <stdio.h>
#include "scanner.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char *tokenNames[] = {NULL, "operador_mas","operador_menos","kw_int","kw_else","kw_for","kw_switch","kw_case","kw_break","kw_continue","punto y coma","parentesis izquierdo","parentesis derecho","identificador","numero","kw_while","coma","llave izquierda","llave derecha","corchete izquierdo","corchete derecho"};

int main(){
	int ntoken, vtoken;
	ntoken = yylex();
	while(ntoken){
		printf("%s es %s\n", yytext,tokenNames[ntoken]);
		ntoken = yylex();
	}
	return 0;
}
