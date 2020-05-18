#include "AnalizadorLexico.h"
#include <fstream>
#include <string>
#include <iostream>

int main(int n, char* arg[]){
	AnalizadorLexico AL;
	if(n == 2){
		std::string path = arg[1];
		AL.scanner(path);
	}
	else if(n == 1){
		std::string path;
		std::cout<<"Ingrese el path del file"<<std::endl;
		std::cin>> path;
		AL.scanner(path);
	}
}
