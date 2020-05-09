#include <iostream>
#include <string>

using namespace std;

bool es_identificador(string);
bool es_digito(char);
bool es_letra(char);

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
	int estado = 1;
	int i = 0;
	char simbolo = buffer[0];
	while(simbolo != '\0' ){
		switch(estado){
			case 1:
				if(es_digito(simbolo))
					estado = 2;
				else if(es_letra(simbolo))
					estado = 3;
				else
					return false;
				break;
			case 2:
				return false;
				break;
			case 3:
				if(es_letra(simbolo))
					estado = 3;
				else if(es_digito(simbolo))
					estado = 3;
				else
					return false;
				break;
		}
		simbolo = buffer[++i];
	}
	if(estado != 3)
		return false;
	else
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
