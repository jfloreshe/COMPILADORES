#include "Automata.h"
#include <iostream>
#include <string>

int Entrada::globalE = 0;
int Estado::globalEs = 0;
int main(){
	std::string path;
	std::cout<<"Ingrese el path del file: ";
	std::cin>>path;
	Automata automataIdentificador{path};
	std::cout<<"Envie s para parar el programa"<<std::endl;
	std::string word;
	do{
		std::cin>>word;
		if(automataIdentificador.reconocer(word,"1"))
			std::cout<<"token reconocido"<<std::endl;
		else
			std::cout<<"error"<<std::endl;
		if(word=="s")
			break;
	}
	while(true);	
}
