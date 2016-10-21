#include "stdafx.h"
#include "Estado.h"


Estado::Estado(string cnombre, bool cinicial, bool csalida)
{
	nombre = cnombre;
	inicial = cinicial;
	salida = csalida;
}

Estado::Estado()
{
}


Estado::~Estado()
{
}

string Estado::getNombre()
{
	return nombre;
}

void Estado::setNombre(string snombre)
{
	nombre = snombre;
}

bool Estado::esInicial()
{
	return inicial;
}

bool Estado::esFinal()
{
	return salida;
}
