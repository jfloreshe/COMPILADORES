#ifndef ANALIZADOR_LEXICO
#define ANALIZADOR_LEXICO

#include <string>
#include <utility>
#include <vector>
#include <fstream>


enum Token{ 
		TKN_OPMAS = '+',TKN_OPMENOS = '-',TKN_OPMUL = '*',TKN_OPDIV = '/',
		TKN_PARI = '(',TKN_PARD = ')',TKN_LLAI = '{',TKN_LLAD = '}',
		TKN_COI = '[',TKN_COD = ']',
		TKN_COMA = ',',TKN_PUNTOYCOMA = ';',
		TKN_COMPMAYOR = '>',TKN_COMPMENOR = '<',TKN_ASIG = '=',TKN_NEGACION = '!', 
		TKN_IDENTIFICADOR=256,TKN_NUMERO,
		TKN_IF,TKN_ELSE,TKN_WHILE,TKN_FOR,TKN_SWITCH,TKN_CASE,TKN_BREAK,TKN_CONTINUE,
		TKN_BOOL,TKN_INT,TKN_FLOAT,TKN_CHAR,
		TKN_VOID,TKN_RETURN,
		TKN_COMPMAYORIGUAL, TKN_COMPMENORIGUAL, TKN_DIFERENTE, TKN_COMPIGUAL};

struct ComponenteLexico{
	char lexema[256];
	Token token;
	ComponenteLexico(std::string _lexema,Token _ctoken):token{_ctoken}{
		int i = 0;
		while(_lexema[i] != '\0'){
			lexema[i] = _lexema[i];
			i++;
		}
		lexema[i] = '\0';	
	}
	ComponenteLexico(){}
};
class AnalizadorLexico{
	private:
		std::vector<ComponenteLexico* > bufferComponenteLexico;
		bool es_digito(char);
		bool es_letra(char);//TODO EN el identificador revisar caso _
		bool es_simbolo_conocido(char);
		Token es_palabra_reservada();
		char lexema[256];
	public:
		void scanner(std::string );
		void mostrar();

};
#endif

