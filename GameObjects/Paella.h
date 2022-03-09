#pragma once
#include "ObjetoPortable.h"
#include "Ingrediente.h"
#include <list>

enum Tama�o{Minima,Mediana,Grande};
enum Estado { Preparacion, Coccion, Preparada };
enum Resultado { Cruda, PocoHecha, Perfecta, MuyHecha, Quemada, Incomestible };
enum Contenido { Limpia, Entera, Mitad, Sucia };

class Paella : public ObjetoPortable
{	
	const int MAX_INGR = 3;
	double tiempoCocion = 0.0, tiempo = 0;

	Estado estado;
	Tama�o tama�o;
	Resultado estadoFinal;

	vector<int> tiemposDeCoccion = {14000, 20000, 25000, 28000, 33000, 38000};

	int sumaIntervalo = 0;


	list<Ingrediente> ingredientes;

public:
	
	Paella(Tama�o tama�o_);
	~Paella() {};

	void a�adeIngr(Ingrediente ingr_);
	void setState(Estado estado_);
	void update() override;
	Estado getState();

};

