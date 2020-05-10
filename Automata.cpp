/*/////////////////////////////////////////////////////////////////
Autor: Jefferson Flores Herrera
Clase que reconoce un automata en formato de tablas
Formato:
alfabetos,estados, transiciones.
-los alfabetos deben ir ante del primer ;
i.e digito{12345\}simbolo{.,-\}; 
*Por ahora el automata no diferencia si un simbolo se esta usando dos veces
*Secuencias de escape reconocidas por ahora salto de linea y findecadena
*para terminar la lista de simbolos usar \
-Los estados deben ir en la segunda linea
i.e 1,2,3,4,5; a,b; se puede usar cualquier nombre como estado terminar con ;
-Las transiciones deben ir separadas por , y en el siguiente formato :
* estado1(entrada,estado2);
*estado1 y estado 2 es cualquiera listado en la linea 2
*entrada es el nombre de tu alfabeto como digito,simbolo,etc
TODO/////////////////////////////////////////////////////////////
-convertir una expresion regular a tabla
-arreglar mas secuencias, rangos en los alfabetos 

*/////////////////////////////////////////////////////////////
#include "Automata.h"
#include <utility>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum Etapa{PASO1,PASO2,PASO3};
Automata::Automata(string path){
	totalEstados = 0;
	totalEntradas = 0;
	if(inicializar_automata(path)){
		cout<<"Automata inicializado exitosamente\n";
	}
	else
		cout<<"Automata fallo al inicializarse\n";
}
bool Automata::estado_entrada_estado(string estadoUnoDefinicion,string def,string estadoDosDefinicion){
	
	cout<<estadoUnoDefinicion<<' '<<def<<' '<<estadoDosDefinicion<<endl;
	for(auto& es: estados){
		if(es->alias == estadoUnoDefinicion){
			for(auto& par: es->tabla){
				if(par.first->definicion == def){
					for(auto& e2:estados){
						if(e2->alias == estadoDosDefinicion){
							par.second = e2;
							return true;
						}
					}								
				}
			}
		}
	}
	return false;
}

bool Automata::inicializar_automata(string path){

	ifstream fileEntrada{path};
	if(fileEntrada)
		cout<<"Se cargo con exito el file "<<path<<endl;
	char character, prevCharacter;
	int linea = 1;
	bool agregandoSimbolos = false;
	vector<char> temporalEntrada;
	string newDefinicion;
	
	Etapa transicionCompleta = PASO1;
	string lineaTresEstadoUno;
	string lineaTresEstadoDos;
	string lineaTresEntrada;
	int totalTransiciones = 0;
	while( fileEntrada >> character){
		temporalEntrada.push_back(character);
		if(linea == 1){
			if(!agregandoSimbolos && character == '{'){
				agregandoSimbolos = true;
				for(auto c: temporalEntrada){
					if(c!='{'){
						newDefinicion += c; 
					}
				}	
				//todo add condicional para entradas sin nombre
				temporalEntrada.clear();
				Entrada* entrada = new Entrada;
				entrada -> id = totalEntradas;
				entrada -> definicion = newDefinicion;
				this -> entradas.push_back(entrada);
				for(auto e: entradas){
					cout<<"entradas actuales: "<< e ->definicion <<endl;
				}
				newDefinicion = "";
			}
			else if(!agregandoSimbolos && character == ',' && prevCharacter == '}'){
				temporalEntrada.clear();
			}
			else if(!agregandoSimbolos && character == ';' && prevCharacter == '}'){
				temporalEntrada.clear();
				linea++;
			}
			else if(!agregandoSimbolos){
				prevCharacter = character;
				continue;
			}
			else if(agregandoSimbolos){

				if(character == '\\'){
					//do nothing
					prevCharacter = character;
				}
				else{
					if(prevCharacter !='\\'){
					//todo para mejorar ver si un elemento se repite
						entradas[totalEntradas]->simbolosAceptados.push_back(character);
					}
					else{
						if(character == 'n')
							entradas[totalEntradas]->simbolosAceptados.push_back('\n');
						else if(character == '0')
							entradas[totalEntradas]->simbolosAceptados.push_back('\0');
						else if(character == '}'){//posible error de prevCharacter not defined undefined behaviour
							agregandoSimbolos = false;
							++totalEntradas;
							temporalEntrada.clear();
							cout<<"LINEA 1 FINISHED\n";
						}//todo agregar mas comandos de backslash
					}
				}
			}
			else
				return false;			
		}
		else if(linea == 2){
			if(character == ',' || character == ';'){
				for(auto c: temporalEntrada){
					if(c != ',' && c != ';')
						newDefinicion += c;
				}
				temporalEntrada.clear();
				Estado* estado = new Estado;
				estado -> id = totalEstados++;
				estado -> alias = newDefinicion;
				this -> estados.push_back(estado);
				newDefinicion = "";
				if(character == ';'){
					++linea;
					for(auto e: estados){
						for(auto entry: entradas){
							e->tabla.push_back(std::make_pair(entry,nullptr));
						}
					}	
					estado = new Estado;
					estado -> id = totalEstados++;
					estado -> alias = "aceptar";
					this -> estados.push_back(estado);
					estado = new Estado;
					estado -> id = totalEstados++;
					estado -> alias = "error";
					this -> estados.push_back(estado);
				}			
			cout<<"LINEA 2 FINISHED\n";
			}
		}
		else if(linea == 3){

			if(transicionCompleta == PASO1 && character == '('){
				cout<<"PASO1"<<endl;
				for(auto c: temporalEntrada){
					if(c != '(')
						lineaTresEstadoUno += c;
				}
				temporalEntrada.clear();	
				transicionCompleta = PASO2;			
			}
			else if(transicionCompleta == PASO2 && character == ','){
				cout<<"PASO2"<<endl;
				for(auto c: temporalEntrada){
					if(c != ',')
						lineaTresEntrada += c;
				}
				temporalEntrada.clear();
				transicionCompleta = PASO3;
			}
			else if(transicionCompleta == PASO3 && character == ')'){
				cout<<"PASO3"<<endl;
				for(auto c: temporalEntrada){
					if(c != ')')
						lineaTresEstadoDos += c;
				}
				temporalEntrada.clear();
				if(estado_entrada_estado(lineaTresEstadoUno,lineaTresEntrada,lineaTresEstadoDos)){
					lineaTresEstadoUno = "";
					lineaTresEntrada = "";
					lineaTresEstadoDos = "";
					transicionCompleta = PASO1;	
				}
				else{
					cerr<<"No se pudo asignar la tabla\n";
					fileEntrada.close();
					return false;
				}			
			}
			else if(transicionCompleta == PASO1 && character == ';'){
				fileEntrada.close();
				return true;
			}
			else if(transicionCompleta == PASO1 && character == ','){
				temporalEntrada.clear();
			}
					
		}
		prevCharacter = character;
	}	
	fileEntrada.close();
}

Estado* Automata::search(string _alias)const{
	for(auto& estado: estados){
		if(estado->alias ==	_alias)
			return estado;
	}
	return nullptr;
}
void Automata::mostrar_simbolos_permitidos()const{
	for(auto e:entradas){
		cout<<e->simbolosAceptados.size()<<": ";
		for(auto s:e->simbolosAceptados){
			cout<<s;
		}
		cout<<"\\\0\\"<<endl;
	}
}

Estado* Automata::search(Estado* e,Entrada* entrada)const{
	for(auto& estadoRetorno: estados){
		if(estadoRetorno -> alias == e -> alias){
			for(auto& par: estadoRetorno->tabla){
				if(par.first -> definicion == entrada -> definicion){
					return par.second;
				}
			}
		}
	}
	return nullptr;
}
Entrada* Automata::reconocerSimbolo(char c)const{
	for(auto& entrada: entradas){
		for(auto s: entrada->simbolosAceptados){
			if(c == s)
				return entrada;
		}
	}
	return nullptr;
}

bool Automata::reconocer(string buffer,string estadoInicial)const{
	Estado* estadoActual = search(estadoInicial);
	int i=0;
	if(estadoActual){
		while( estadoActual->alias != "aceptar"){
			char simbolo = buffer[i++];
			Entrada* entradaTemp = reconocerSimbolo(simbolo);
			if(entradaTemp){
				estadoActual = search(estadoActual,entradaTemp);
				if(estadoActual){
					if(estadoActual->alias == "error"){
						return false;
					}
				}
				else{
					cout<<"248"<<endl;
					return false;
				}
			}
			else{
				cout<<"253"<<endl;
				return false;
			}
		}
		return true;
	}
	else
		return false;
}
void Automata::mostrar_automata()const{
	for(auto objeto: estados){
			cout<< objeto->alias<< ": ";
		for(auto par:objeto->tabla){
			cout<<par.first->definicion<<' '<<par.second->alias<<endl;
		}
	}
}

Automata::~Automata(){
	for(auto o:entradas)
		delete o;
	for(auto o:estados)
		delete o;
}
