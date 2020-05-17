#include <iostream>
#include <string>
using namespace std;

bool es_identificador(string);
bool es_digito(char);
bool es_letra(char);

enum Estado{estado1,estado2,estado3,totalEstados,ACEPTAR,ERROR};
enum Entrada{digito,letra,FDC,totalEntradas};

int main(){
	cout<<"Envie s para parar el programa"<<endl;
	string word;
	do{
		cin>>word;
		if(es_identificador(word))
			cout<<"token reconocido"<<endl;
		else
			cout<<"error"<<endl;
		if(word=="s")
			break;
	}
	while(true);
}

bool es_identificador(string buffer){
	Estado tabla[totalEstados][totalEntradas];
	tabla[estado1][digito] = estado2;
	tabla[estado1][letra] = estado3;
	tabla[estado1][FDC] = ERROR;
	tabla[estado2][digito] = ERROR;
	tabla[estado2][letra] = ERROR;
	tabla[estado2][FDC] = ERROR;
	tabla[estado3][digito] = estado3;
	tabla[estado3][letra] = estado3;
	tabla[estado3][FDC] = ACEPTAR;

	Estado estado = estado1;
	Entrada entrada;
	int i=0;
	while(estado != ACEPTAR){
		char simbolo = buffer[i++];
		if(es_digito(simbolo))
			entrada = digito;
		else if(es_letra(simbolo))
			entrada = letra;
		else if(simbolo == '\0'){
			std::cout<<"findecadena\n";
			entrada = FDC;
		}
		estado = tabla[estado][entrada];
		if (estado == ERROR)
			return false;
	}
	return true;
}

bool es_digito(char c){
	if(c>='0' && c<='9')
		return true;
	else
		return false;
}
bool es_letra(char c){
	if( (c>='a' && c<='z') || (c>='A' && c<='Z'))
		return true;
	else 
		return false;
}
