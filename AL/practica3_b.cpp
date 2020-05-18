#include "AnalizadorLexico.h"
#include <fstream>
#include <string>
#include <iostream>

int main(){
	std::string path = "Automata.h";
	std::ifstream file{path,std::ios::binary};
	std::cout<<"linea 9";
	AnalizadorLexico AL;
	std::cout<<"linea 10";
	AL.scanner(file);
//	AL.mostrar();
	file.close();
}
