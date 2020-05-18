#ifndef AUTOMATA_H
#define AUTOMATA_H
/*////////////
Autor: Jefferson Flores Herrera
Clase creada para automatizar reconocimiento de una cadena
en un lenguaje dado(exp regular),automata finito dado en forma de tabla en un archivo.
//////////// */

#include <string>
#include <utility>
#include <iostream>
#include <vector>

struct Entrada{
	static int globalE;
	int id;
	std::string definicion;
	std::vector<char> simbolosAceptados;//porfavor no repita los simbolos,
	Entrada(){std::cout<<"new entrada";++globalE;}
	~Entrada(){std::cout<<"eliminando entrada"<<--globalE;}
};
struct Estado{
	static int globalEs;
	int id;
	std::string alias;
	std::vector<std::pair<Entrada*,Estado*>> tabla;
	Estado(){std::cout<<"new estado";++globalEs;}
	~Estado(){std::cout<<"eleminando estado"<<--globalEs;}
};

class Automata{
	private:
		std::vector<Entrada*> entradas;
		std::vector<Estado*> estados;
		int totalEstados;
		int totalEntradas;
		Estado* search(std::string)const;
		Estado* search(Estado*,Entrada*)const;
		Entrada* reconocerSimbolo(char)const;
		bool estado_entrada_estado(std::string ,std::string, std::string);
		bool inicializar_automata(std::string);		
	public:
		Automata(std::string path);
		~Automata();
		int get_total_estados() const{return totalEstados;}
		int get_total_entradas() const{return totalEntradas;}
		bool reconocer(std::string,std::string) const;	
		void mostrar_simbolos_permitidos()const;
		void mostrar_automata()const;
};
#endif
