#pragma once
#include <list>

class Comanda;

using namespace std;

class ListaComandas
{
	list<Comanda*> lista;
public:
	//A�ade la comanda que escribe el camarero a la lista
	void A�adeComanda(Comanda* comanda);

	//Interfaz
	void render();
};

