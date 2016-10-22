#include "Estado.h"
#include <vector>
#include <iostream>

using namespace std;

class Automata
{
private:
	vector<Estado> estados;
	vector<string> alfabeto_entrada;
	Estado **matriz;
	Estado estado_inicial;
	vector<string> palabra_del_lenguaje;
	Estado estado_actual;

public:
	Automata();
	//Automata(vector<Estado>, vector<char>);
	~Automata();
	//void crear_tabla_f(vector<Estado>*, vector<char>*);
	void crear_tabla_f();
	void rellenar();
	void mostrar_tabla_f();
	void ingresar_alfabeto();
	void ingresar_estados();
	void comprobar_palabra();
	void mostrar_palabra_lenguaje();
	int buscarAlfabeto(string);
	int buscarEstado(string);
	void ingreso_alfabeto_repetido();
	void ingreso_estados_repetido();
	Estado ingresar_info_estado();
};

