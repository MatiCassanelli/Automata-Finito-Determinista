// Automatas.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Automata.h"


int main()
{
	Automata automata= Automata();

	automata.mostrar_tabla_f();
	//automata.comprobar_palabra();	//para version de Mati

	cout << endl << "Ingrese @ si quiere ingresar otra palabra." << endl << endl;	//version de Felipe
	do {
		automata.comprobar_palabra();
		cout << endl << endl << "Ingrese nueva palabra:" << endl;
	} while (0 != 1);

	
	system("Pause");
    return 0;
}

