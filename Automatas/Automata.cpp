#include "stdafx.h"
#include "Automata.h"


Automata::Automata()
{	
	int aux = 0;	//armar una funcion que se encargue del ingreso de todo y no hacerlo desde aca!!
	do
	{
		ingresar_alfabeto();
		cout << "Ingresar otro elemento del alfabeto de entrada? " << endl << "0 = No" << endl << "1 = Si" << " "<<endl;
		cin >> aux;
	} while (aux != 0);
	do
	{
		ingresar_estados();
		cout << "Ingresar otro estado ? " << endl << "0 = No" << endl << "1 = Si" << " "<<endl;
		cin >> aux;
	} while (aux != 0);
	
	crear_tabla_f();
}

Automata::~Automata()
{
}

void Automata::crear_tabla_f()	//usando matriz de estados
{
	//inicializo la matriz de acuerdo a la cant de estados y de elementos del alfabeto de entrada
	matriz = new Estado*[estados.size()];				//filas
	for (int i = 0; i < estados.size()+1; i++)
		matriz[i] = new Estado[alfabeto_entrada.size()+1];	//columnas

	for (int i = 1; i < alfabeto_entrada.size()+1; i++)	//completo la primer fila con los elementos del alfabeto
		matriz[0][i].setNombre(alfabeto_entrada[i-1]);
	for (int j = 1; j < estados.size()+1; j++)			//completo la primer columna con los estados 
		matriz[j][0].setNombre(estados[j-1].getNombre());
	matriz[0][0].setNombre(" ");
	rellenar();
}


void Automata::rellenar()	//con matriz de estados
{
	string ingreso;
	for (int j = 0; j < estados.size(); j++)
		for (int i = 0; i < alfabeto_entrada.size(); i++)
		{
			int k = 0;
			cout << "Usted esta en el estado " << estados[j].getNombre() << " y viene el elemento " <<	
				alfabeto_entrada[i] << " pasamos al estado: ";
			cin >> ingreso;

			//while (k < estados.size() && estados[k].getNombre() != ingreso)
			//	k++;
			//if (k >= estados.size())
			//	cout << "Estado no existente. Ingrese uno nuevamente";
			while (buscarEstado(ingreso) == -1)
			{
				cout << "Estado no existente. Ingrese uno nuevamente";
				cin >> ingreso;
			}
			
			matriz[j+1][i+1] = estados[buscarEstado(ingreso)];
		}
}

void Automata::mostrar_tabla_f()	//con matriz de char
{
	for (int i = 0; i < estados.size() + 1; i++)
	{
		for (int j = 0; j < alfabeto_entrada.size() + 1; j++)
			cout << matriz[i][j].getNombre() << "\t";
		cout << endl;
	}
}

void Automata::ingresar_alfabeto()
{
	cout << "Ingrese elemento componente del alfabeto de entrada ";
	fflush(stdout);
	string ingreso;
	cin >> ingreso;
	//int B = 0;	//bandera para realizar controles a la nueva palabra que ingrese en caso de que este repetida
	if (!alfabeto_entrada.empty())
	{
		//while (B == 0)
		//{
		//	B = 1;
		//	for (int i = 0; i<alfabeto_entrada.size(); i++)
		//	{
		//		if (alfabeto_entrada[i] == ingreso)
		//		{
		//			cout << "Elemento existente. Ingrese uno distinto ";
		//			cin >> ingreso;
		//			B = 0;
		//			i = alfabeto_entrada.size();
		//		}
		//	}
		//}
		
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
	bool inicial, salida;
	string nombre;
	Estado estado_ingresado = Estado();

	cout << "Ingrese nombre del estado ";
	cin >> nombre;

	cout << "Estado Inicial?" << endl << "0 = No" << endl << "1 = Si" << " "<<endl;
	cin >> inicial;

	cout << "Estado de Salida?" << endl << "0 = No" << endl << "1 = Si" << " "<<endl;
	cin >> salida;

	if (!estados.empty())
	{
		if (inicial == 1)
		{
			for (int i = 0; i<estados.size(); i++)
			{
				if (estados[i].esInicial())
				{
					cout << "No puede haber dos estados iniciales. Se convirtio el estado actual en uno NO inicial";//Podriamos hacer que vuelva a ingresar estado
					inicial = 0;
				}
			}
		}
	//	int B = 0; //bandera para controlar si el nuevo nombre que ingresa para el estado no está repetido
	//	while (B == 0)
	//	{
	//		B = 1;
	//		for (int i = 0; i<estados.size(); i++)
	//		{
	//			if (estados[i].getNombre() == nombre)
	//			{
	//				cout << "Estado existente. Ingrese uno distinto ";
	//				cin >> nombre;
	//				B = 0;
	//				i = estados.size();
	//			}
	//		}
	//	}
		while (buscarEstado(nombre) != -1)
		{
			cout << "Estado existente. Ingrese uno distinto ";
			cin >> nombre;
		}
	}

	estado_ingresado = { nombre,  inicial,  salida };
	estados.push_back(estado_ingresado);
	if(estado_ingresado.esInicial())
		estado_inicial = estado_ingresado;
}

void Automata::comprobar_palabra()	//hacer para que ingrese de a un solo caracter, y no palabra entera
{
	string ingreso = "5", parche;
	Estado estado_actual = estado_inicial;
	while (ingreso != " ")
	{
		cin >> ingreso;
		for (int k = 0;k < ingreso.size();k++)
		{
			parche = ingreso[k];
			int i = 0, j = 0;
			//busca posicion estado actual para indice de la matriz
			while (j < estados.size() && estados[j].getNombre() != estado_actual.getNombre())
				j++;
			//busca posicion del elementos del alfabeto para indice de la matriz
			while (i < alfabeto_entrada.size() && alfabeto_entrada[i] != parche)
				i++;
			if (i >= alfabeto_entrada.size())
				cout << "Ingreso un elemento no existente en el alfabeto de entrada" << endl;
			else
				estado_actual = matriz[j+1][i+1];
		}
		if (estado_actual.esFinal())
		{
			cout << "Ingreso una palabra existente en el lenguaje " << endl;
			palabra_del_lenguaje.push_back(ingreso);
		}
		else
			cout << "Ingreso una palabra NO existente en el lenguaje " << endl;
		estado_actual = estado_inicial;
	}
}

void Automata::mostrar_palabra_lenguaje()
{
	for (int i = 0; i < palabra_del_lenguaje.size(); i++)
		cout << palabra_del_lenguaje[i]<<endl;
	
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

		
	



