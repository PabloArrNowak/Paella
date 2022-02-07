#pragma once
#include <vector>

class Paella;
class Ingrediente;

using namespace std;
using uint = uint32_t;

class Comanda
{
public:
	enum Tama�o { Peque�a, Mediana, Grande };
	
	//Compara las paellas recibidas con el pedido y le pone la puntuaci�n
	float Puntuacion(vector<Paella*> paellas);
private:
	uint numeroMesa;
	uint numeroPaellas;

	//Por cada paella, un tama�o y un vector de ingredientes
	vector<Tama�o> tama�os;
	vector<vector<Ingrediente*>> ingredientes;
};

