#include "stdafx.h"
#include "Automata.h"
#include <conio.h>


Automata::Automata()
{	
	ingreso_alfabeto_repetido();
	ingreso_estados_repetido();
	crear_tabla_f();
}

Automata::~Automata()
{
}

void Automata::crear_tabla_f()	
{
	matriz = new Estado*[estados.size()];				//filas
	for (int i = 0; i < estados.size(); i++)
		matriz[i] = new Estado[alfabeto_entrada.size()];	//columnas

	rellenar();
}


void Automata::rellenar()	
{
	string ingreso;
	for (int j = 0; j < estados.size(); j++)
		for (int i = 0; i < alfabeto_entrada.size(); i++)
		{
			int k = 0;
			cout << "Usted esta en el estado " << estados[j].getNombre() << " y viene el elemento " <<
				alfabeto_entrada[i] << " pasamos al estado: ";
			cin >> ingreso;

			while (buscarEstado(ingreso) == -1)
			{
				cout << "Estado no existente. Ingrese uno nuevamente";
				cin >> ingreso;
			}
			matriz[j][i] = estados[buscarEstado(ingreso)];
		}
}

void Automata::mostrar_tabla_f()
{
	for (int i = 0; i < estados.size(); i++)	//filas			
	{
		if (i == 0) {
			cout << '\t';
			for (int k = 0; k < alfabeto_entrada.size(); k++)
				cout << alfabeto_entrada[k] << '\t';
			cout << endl;
		}
		for (int j = 0; j < alfabeto_entrada.size(); j++)	//columnas
		{
			if (j == 0) 
			{
				if (estados[i].esInicial())
					cout << "->"; 
				else
					cout << "  ";

				cout << estados[i].getNombre();	
				if (estados[i].esFinal())
					cout << '*';
				cout << '\t';
			}
			cout << matriz[i][j].getNombre() << "\t";
		}
		cout << endl;
	}
}

void Automata::ingresar_alfabeto()
{
	cout << "Ingrese elemento componente del alfabeto de entrada ";
	fflush(stdout);
	string ingreso;
	cin >> ingreso;
	if (!alfabeto_entrada.empty())
	{		
		while (buscarAlfabeto(ingreso) != -1)
		{
			cout << "Elemento existente. Ingrese uno distinto ";
			cin >> ingreso;
		}
	}
	alfabeto_entrada.push_back(ingreso);
}

void Automata::ingresar_estados()
{
	int i = 0;
	Estado estado_ingresado = ingresar_info_estado();

	if (!estados.empty())
	{
		if (estado_ingresado.esInicial() == 1)
		{
			for (int i = 0; i<estados.size(); i++)
			{
				if (estados[i].esInicial())
				{
					cout << "No puede haber dos estados iniciales. Se convirtio el estado actual en uno NO inicial";
					estado_ingresado.cambiar_inicial(false);
				}
			}
		}
	}
	estados.push_back(estado_ingresado);
	if (estado_ingresado.esInicial())
		estado_inicial = estado_ingresado;
}

//void Automata::comprobar_palabra()	//no permite ingresar un elemento q NO forme parte del alfabeto de entrada
//{
//	
//	char ingreso = '5';
//	string parche;
//	Estado estado_actual = estado_inicial;
//	vector <char> palabra;
//	while (ingreso != '@')
//	{
//		int i = 0, j = 0;
//
//		ingreso = _getch();
//		parche = ingreso;
//		if(buscarAlfabeto (parche)!=-1)
//			palabra.push_back(ingreso);
//		for (int i = 0; i < palabra.size(); i++)
//			cout << palabra[i];
//
//		i = buscarAlfabeto(parche);
//		j = buscarEstado(estado_actual.getNombre());
//
//		//int i = 0, j = 0;
//
//		//ingreso = _getch();
//		//palabra.push_back(ingreso);
//		//for (int i = 0; i < palabra.size(); i++)
//		//	cout << palabra[i];
//		//for (int k = 0;k < ingreso.size();k++)
//		//{*/
//		//parche = ingreso;
//
//		//i = buscarAlfabeto(parche);
//		//j = buscarEstado(estado_actual.getNombre());
//
//		if (i == -1)
//			cout << endl << "Ingreso un elemento no existente en el alfabeto de entrada" << endl;
//		else
//		{	//si felipe dice q no, borrar estas llaves, descomentar lo comentado, y comentar lo no comentado
//			estado_actual = matriz[j][i];	
//
//			if (estado_actual.esFinal())
//				cout << endl << "Ingreso una palabra existente en el lenguaje " << endl;
//			else
//				cout << endl << "Ingreso una palabra NO existente en el lenguaje " << endl;
//		}		
//	}
//}

void Automata::comprobar_palabra()	//deja ingresar un elemento q no sea del alfabeto de entrada, pero dsp de eso no da mas salidas
{

	char ingreso = '5';
	string parche;
	bool FAIL = false;
	Estado estado_actual = estado_inicial;
	vector <char> palabra;
	while (ingreso != '@')
	{
		int i = 0, j = 0;
		ingreso = _getch();
		if (ingreso != '@') {
			parche = ingreso;
			palabra.push_back(ingreso);
			for (int i = 0; i < palabra.size(); i++)
				cout << palabra[i];

			i = buscarAlfabeto(parche);
			j = buscarEstado(estado_actual.getNombre());

			if (i == -1) {
				cout << endl << "Ingreso un elemento no existente en el alfabeto de entrada" << endl;
				cout << "Ingreso una palabra NO existente en el lenguaje " << endl;
				FAIL = true;
			}
			else
			{
				estado_actual = matriz[j][i];

				if (estado_actual.esFinal() && FAIL == false)
					cout << endl << "Ingreso una palabra existente en el lenguaje " << endl;
				else
					cout << endl << "Ingreso una palabra NO existente en el lenguaje " << endl;
			}//Fin Else
		}
	}//Fin While
}

int Automata::buscarAlfabeto(string ingreso)
{
	int i = 0;
	for (; i<alfabeto_entrada.size(); i++)
	{
		if (alfabeto_entrada[i] == ingreso)
			return i;
	}
	return -1;
}

int Automata::buscarEstado(string ingreso)
{
	int i = 0;
	for (int i = 0; i<estados.size(); i++)
	{
		if (estados[i].getNombre() == ingreso)
			return i;
	}
	return -1;
}

void Automata::ingreso_alfabeto_repetido()
{
	int aux = 0;
	do
	{
		ingresar_alfabeto();
		cout << "Ingresar otro elemento del alfabeto de entrada? " << endl << "0 = No" << endl << "1 = Si" << " " << endl;
		cin >> aux;
	} while (aux != 0);
}

void Automata::ingreso_estados_repetido()
{
	int ingreso;
	int aux = existeInicial();
	while (aux == 0)
	{
		do
		{
			ingresar_estados();
			cout << "Ingresar otro estado ? " << endl << "0 = No" << endl << "1 = Si" << " " << endl;
			cin >> ingreso;
			aux = 1;
		} while (ingreso != 0);

		if (existeInicial() == 0)
		{
			cout << "Debe existir un estado inicial obligatoriamente. Debera ingresar todos los estados de nuevo" << endl;
			estados.clear();
			aux = 0;
		}
	}
}

Estado Automata::ingresar_info_estado()
{
	bool inicial, salida;
	string nombre;

	cout << "Ingrese nombre del estado ";
	cin >> nombre;
	while (buscarEstado(nombre) != -1)
	{
		cout << "Estado existente. Ingrese uno distinto ";
		cin >> nombre;
	}

	cout << "Estado Inicial?" << endl << "0 = No" << endl << "1 = Si" << " " << endl;
	cin >> inicial;

	cout << "Estado de Salida?" << endl << "0 = No" << endl << "1 = Si" << " " << endl;
	cin >> salida;

	Estado devolver = { nombre, inicial, salida };
	return devolver;
}

int Automata::existeInicial()
{
	int B = 0;
	for (int i = 0; i < estados.size(); i++)
	{
		if (estados[i].esInicial())
			B = 1;
	}
	return B;
}

		
	



