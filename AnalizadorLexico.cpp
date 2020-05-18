#include "AnalizadorLexico.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

bool AnalizadorLexico::es_digito(char c){
	if(c >= '0' && c <= '9')
		return true;
	return false;
}
bool AnalizadorLexico::es_letra(char c){
	if((c >= 'a' && c <= 'z')|| (c >= 'A' && c<= 'Z'))
		return true;
	return false;
}
bool AnalizadorLexico::es_simbolo_conocido(char c){
	if(c == '*' ||
		c == '+' ||
		c == '-' ||
		c == '/' ||
		c == '>' ||
		c == '<' ||
		c == '=' ||
		c == '!' ||
		c == '(' ||
		c == ')' ||
		c == '{' ||
		c == '}' ||
		c == '[' ||
		c == ']' ||
		c == ',' ||
		c == ';' )
		return true;
	return false;

}
Token AnalizadorLexico::es_palabra_reservada(){
	std::string identificador;
	identificador.assign(lexema);
	Token t = Token::TKN_IDENTIFICADOR;
	if(identificador.compare("if") == 0)
		t = Token::TKN_IF;
	else if(identificador.compare("else") == 0)
		t = Token::TKN_ELSE;
	else if(identificador.compare("while") == 0)
		t = Token::TKN_WHILE;
	else if(identificador.compare("for") == 0)
		t = Token::TKN_FOR;
	else if(identificador.compare("switch") == 0)
		t = Token::TKN_SWITCH;
	else if(identificador.compare("case") == 0)
		t = Token::TKN_CASE;
	else if(identificador.compare("break") == 0)
		t = Token::TKN_BREAK;
	else if(identificador.compare("continue") == 0)
		t = Token::TKN_CONTINUE;
	else if(identificador.compare("int") == 0)
		t = Token::TKN_INT;
	else if(identificador.compare("float") == 0)
		t = Token::TKN_FLOAT;
	else if(identificador.compare("bool") == 0)
		t = Token::TKN_BOOL;
	else if(identificador.compare("char") == 0)
		t = Token::TKN_CHAR;
	else if(identificador.compare("void") == 0)
		t = Token::TKN_VOID;
	else if(identificador.compare("return") == 0)
		t = Token::TKN_RETURN;
	
	return t;
}
void AnalizadorLexico::mostrar(){
	for(auto cl: bufferComponenteLexico){
		switch(cl -> token){
			case TKN_UNDEFINED: printf("token = UNDEFINED[%s]\n", cl -> lexema); break;
			case TKN_OPMAS: printf("token = OPMAS[%s]\n",cl -> lexema); break;
			case TKN_OPMENOS: printf("token = OPMENOS[%s]\n",cl -> lexema); break;
			case TKN_OPMUL: printf("token = OPMUL[%s]\n",cl -> lexema); break;
			case TKN_OPDIV: printf("token = OPDIV[%s]\n",cl -> lexema); break;
			case TKN_PARI: printf("token = PARI[%s]\n",cl -> lexema); break;
			case TKN_PARD: printf("token = PARD[%s]\n",cl -> lexema); break;
			case TKN_LLAI: printf("token = LLAI[%s]\n",cl -> lexema); break;
			case TKN_LLAD: printf("token = LLAD[%s]\n",cl -> lexema); break;
			case TKN_COI: printf("token = COI[%s]\n",cl -> lexema); break;
			case TKN_COD: printf("token = COD[%s]\n",cl -> lexema); break;
			case TKN_COMA: printf("token = COMA[%s]\n",cl -> lexema); break;
			case TKN_PUNTOYCOMA: printf("token = PUNTOYCOMA[%s]\n",cl -> lexema); break;
			case TKN_COMPMAYOR: printf("token = COMPMAYOR[%s]\n",cl -> lexema); break;
			case TKN_COMPMENOR: printf("token = COMPMENOR[%s]\n",cl -> lexema); break;
			case TKN_ASIG: printf("token = ASIG[%s]\n",cl -> lexema); break;
			case TKN_NEGACION: printf("token = NEGACION[%s]\n",cl -> lexema); break;
			case TKN_IDENTIFICADOR: printf("token = IDENTIFICADOR[%s]\n",cl -> lexema); break;
			case TKN_NUMERO: printf("token = NUMERO[%s]\n",cl -> lexema); break;
			case TKN_IF: printf("token = IF[%s]\n",cl -> lexema); break;
			case TKN_ELSE: printf("token = ELSE[%s]\n",cl -> lexema); break;
			case TKN_WHILE: printf("token = WHILE[%s]\n",cl -> lexema); break;
			case TKN_FOR: printf("token = FOR[%s]\n",cl -> lexema); break;
			case TKN_SWITCH: printf("token = SWITCH[%s]\n",cl -> lexema); break;
			case TKN_CASE: printf("token = CASE[%s]\n",cl -> lexema); break;
			case TKN_BREAK: printf("token = BREAK[%s]\n",cl -> lexema); break;
			case TKN_CONTINUE: printf("token = CONTINUE[%s]\n",cl -> lexema); break;
			case TKN_BOOL: printf("token = BOOL[%s]\n",cl -> lexema); break;
			case TKN_INT: printf("token = INT[%s]\n",cl -> lexema); break;
			case TKN_FLOAT: printf("token = FLOAT[%s]\n",cl -> lexema); break;
			case TKN_CHAR: printf("token = CHAR[%s]\n",cl -> lexema); break;
			case TKN_VOID: printf("token = VOID[%s]\n",cl -> lexema); break;
			case TKN_RETURN: printf("token = RETURN[%s]\n",cl -> lexema); break;
			case TKN_COMPMAYORIGUAL: printf("token = COMPMAYORIGUAL[%s]\n",cl -> lexema); break;
			case TKN_COMPMENORIGUAL: printf("token = COMPMENORIGUAL[%s]\n",cl -> lexema); break;
			case TKN_DIFERENTE: printf("token = DIFERENTE[%s]\n",cl -> lexema); break;
			case TKN_COMPIGUAL: printf("token = COMPIGUAL[%s]\n",cl -> lexema); break;
		}
		delete cl;
	}
	bufferComponenteLexico.clear();
}
void AnalizadorLexico::scanner(std::string path){
	std::ifstream file{path,std::ios::binary};
	char characterRead;
	int i;
	Token cToken;
	file >> std::skipws;
	ComponenteLexico* tempCL;
	while( file.peek() != EOF){ 
		file>>characterRead;
		
		if(es_letra(characterRead)){//Reconoce si es identificador, palabra reservada
			i = 0;
			file >> std::noskipws;
			do{
				lexema[i++] = characterRead;
				file >> characterRead;
			}while( es_digito(characterRead) || es_letra(characterRead) || characterRead == '_');
			lexema[i] = '\0';
			if(characterRead != ' ' && characterRead != '\n' && characterRead != '\t'){
				file.putback(characterRead);
				cToken = es_palabra_reservada();
				bufferComponenteLexico.push_back( new ComponenteLexico(lexema,cToken));
			}
			else if(characterRead == ' ' || characterRead == '\n' || characterRead == '\t'){
				file>>std::skipws;
				cToken = es_palabra_reservada();
				bufferComponenteLexico.push_back( new ComponenteLexico(lexema,cToken));
			}
		}
		else if(es_digito(characterRead)){
			cToken = TKN_NUMERO;
			i = 0;
			do{
				lexema[i++] = characterRead;
				file >> characterRead;
			}while(es_digito(characterRead));
			if(characterRead == '.'){
				do{
					lexema[i++] = characterRead;
					file >> characterRead;
				}while( es_digito(characterRead));
				lexema[i++] = '0';
			}
			lexema[i] = '\0';
			file.putback(characterRead);
			bufferComponenteLexico.push_back( new ComponenteLexico(lexema,cToken));
		}
		else if(es_simbolo_conocido(characterRead)){
			i = 0;
			lexema[i++] = characterRead;
			if(characterRead == '+' || characterRead == '-' || characterRead == '*' || characterRead == '(' || characterRead == ')' || characterRead == ',' || characterRead == ';' || characterRead == '{' || characterRead == '}' || characterRead == '[' || characterRead == ']' ){
				lexema[i] = '\0';
				cToken = static_cast<Token>(lexema[0]);//TODO cambiarlo de type a Token si da error
				bufferComponenteLexico.push_back( new ComponenteLexico(lexema,cToken));
			}
			else if(characterRead == '<'){
				file >> characterRead;
				if(characterRead == '='){
					lexema[0] = '<'; lexema[1] = '='; lexema[2] = '\0';
					cToken = TKN_COMPMENORIGUAL;
				}
				else{
					file.putback(characterRead);
					lexema[0] = '<'; lexema[1] = '\0';
					cToken = static_cast<Token>(lexema[0]);//ver104
				}
				bufferComponenteLexico.push_back( new ComponenteLexico(lexema,cToken));
			}
			else if(characterRead == '>'){
				file >> characterRead;
				if(characterRead == '='){
					lexema[0] = '>'; lexema[1] = '='; lexema[2] = '\0';
					cToken = TKN_COMPMAYORIGUAL;
				}
				else{
					file.putback(characterRead);
					lexema[0] = '>'; lexema[1] = '\0';
					cToken = static_cast<Token>(lexema[0]);//ver104
				}
				bufferComponenteLexico.push_back( new ComponenteLexico(lexema,cToken));
			}
			else if(characterRead == '='){
				file >> characterRead;
				if(characterRead == '='){
					lexema[0] = '='; lexema[1] = '='; lexema[2] = '\0';
					cToken = TKN_COMPIGUAL;
				}
				else{
					file.putback(characterRead);
					lexema[0] = '='; lexema[1] = '\0';//TKN_ASIGNACION
					cToken = static_cast<Token>(lexema[0]);//ver104
				}
				bufferComponenteLexico.push_back( new ComponenteLexico(lexema,cToken));
			}
			else if(characterRead == '!'){
				file >> characterRead;
				if(characterRead == '='){
					lexema[0] = '!'; lexema[1] = '='; lexema[2] = '\0';
					cToken = TKN_DIFERENTE;
				}
				else{
					file.putback(characterRead);
					lexema[0] = '!'; lexema[1] = '\0';//tkn_negacion
					cToken = static_cast<Token>(lexema[0]);//ver104
				}
				bufferComponenteLexico.push_back( new ComponenteLexico(lexema,cToken));
			}
			else if(characterRead == '/'){
				file >> characterRead;
				if(characterRead == '/'){
					file >> std::noskipws;
					do{
						file >> characterRead;
					}while(characterRead != '\n');
					file >> std::skipws;
				}
				else if(characterRead == '*'){
					do{
						file >> characterRead;
						if(characterRead == '*'){
							file >> characterRead;
							if(characterRead == '/')
								break;
						}
					}while(true);//ignora hasta encontrar el* //
				}
				else if(characterRead != '/' && characterRead != '*'){
					file.putback(characterRead);
					lexema[0] = '/'; lexema[1] = '\0';
					cToken = static_cast<Token>(lexema[0]);//ver104
					bufferComponenteLexico.push_back( new ComponenteLexico(lexema,cToken));
				}
			}
		}
		else if(!es_digito(characterRead) && !es_letra(characterRead) && !es_simbolo_conocido(characterRead) ){
			//TODO otros elementos
		}
		mostrar();
		
	}
	file.close();
}

