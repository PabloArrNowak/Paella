#pragma once

#include "Mueble.h"

#include "../../Data/Pool.h"
#include "../Cola.h"

class Game;

class Cliente;

class Puerta : public Mueble
{
	int maxTamGrupo = 0;

	const int MAX_SPAWN_TIME = 18000;
	const int MIN_SPAWN_TIME = 9000;

	const int FAIL_SPAWN_TIME = 5000;

	double spawn_delay = 0;
	double initTime;

	Cola* cola;

	Uint8 orientacion;

	bool clientSpawn();
	int numClientSpawn();

public:
	Puerta(Game* game, Vector2D<double> pos, int t_Max, int maxTamGrupo_);
	~Puerta() = default;

	void update() override;
	virtual bool receiveGrupoClientes(GrupoClientes* gc);

	SDL_Rect getCollider() override;
	SDL_Rect getOverlap() override;

	Cola* getCola();

	void setVel(Vector2D<double> vel_) override;
	

	void setOrientation(Cliente* c);
};









