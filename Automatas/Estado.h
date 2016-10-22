#include <string>
using namespace std;

class Estado
{
private:
	bool inicial = true;
	bool salida = true;
	string nombre;

public:
	Estado(string,bool,bool);
	Estado();
	~Estado();
	string getNombre();
	void setNombre(string);
	bool esInicial();
	bool esFinal();
	void cambiar_inicial(bool);



};

