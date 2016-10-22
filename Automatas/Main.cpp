// Automatas.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Automata.h"


int main()
{
	Automata automata= Automata();
	//int ia = 0, ie = 0;	//esto no sirve
	//do
	//{
	//	automata.ingresar_alfabeto();
	//	cout << "Ingresar otro elemento del alfabeto de entrada? " << endl << "0 = No" << endl << "1 = Si" << " " << endl;
	//	cin >> ia;
	//} while (ia != 0);

	//do
	//{
	//	automata.ingresar_estados();
	//	cout << "Ingresar otro estado ? " << endl << "0 = No" << endl << "1 = Si" << " " << endl;
	//	cin >> ie;
	//} while (ie != 0);
	automata.mostrar_tabla_f();
	automata.comprobar_palabra();
	

    return 0;
}

