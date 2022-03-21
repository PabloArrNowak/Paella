#pragma once
#include "ObjetoPortable.h"
#include "Ingrediente.h"
#include "../Control/ObjectManager.h"
#include <list>


enum Estado { Preparacion, Coccion, Preparada };
enum Resultado { Cruda, PocoHecha, Perfecta, MuyHecha, Quemada, Incomestible };
enum Contenido { Limpia, Entera, Mitad, Sucia };
enum Volumen { Minima, Mediana, Grande };

class Game;

class Paella : public ObjetoPortable
{	

public:
	
	

	Volumen volumen;

	Paella(Game* game, Volumen volumen_);
	~Paella() {};

	void añadeIngr(Ingrediente ingr_);
	void eliminarIngr();
	void setState(Estado estado_);
	void paellaRecogida();
	void update() override;
	void setLavado(Contenido contenidoPaella);

	void onObjectPicked() override;
	void onObjectDropped() override;

	bool canPick() override;

	void changeTexture(string clave);
	Estado getState();


private:
	const int MAX_INGR = 3;
	double tiempoCoccion = 0.0, tiempo = 0.0;
	int sumaIntervalo = 0, i = 0;

	Estado estado = Preparacion;
	Resultado estadoFinal = Cruda;
	Contenido contenido = Limpia;

	vector<int> tiemposDeCoccion = { 14000, 20000, 25000, 28000, 33000, 38000 };

	list<Ingrediente> ingredientes;

	vector<bool> ingrEnPaella;

};

