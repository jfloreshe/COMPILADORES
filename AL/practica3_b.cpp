#include "AnalizadorLexico.h"
#include <fstream>
#include <string>
#include <iostream>

int main(){
	std::string path = "Automata.cpp";
	AnalizadorLexico AL;
	AL.scanner(path);
}
