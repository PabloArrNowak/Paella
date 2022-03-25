#pragma once

#include <vector>
#include <List>;

#include "Cliente.h"

#include "PoolObject.h"
#include "ObjetoPortable.h"

#include "../Data/Comanda.h"

class Cola;
class Pedido;
class Game;

enum EstadoClientes { CAMINANDO, ENCOLA, PIDIENDO, CUENTA };

class GrupoClientes : public PoolObject
{
	const unsigned int DIMENSION = 60;

	vector<Cliente*> clientes;

	list<GrupoClientes*>::const_iterator posCola;
	Cola* cola;

	const float DIMIN_TIME = 3000;
	const float DIMIN_TOLERANCIA = 2;
		
	float lastTimeTol;
	float tolerancia;
	bool showTol;

	Texture* texTolerancia;


	float lastTimePed;
	int itemNow;
	bool showPed;
	bool orderStart;
	Pedido* pedido;
	vector<string> texPedido;
	
	const float PED_DELAY = 2000;

	EstadoClientes estado_;

	int mitadGrupo();

	void bajaTolerancia();

public:
	GrupoClientes(Game* game);	
	~GrupoClientes() = default;

	void initGrupo(Cola* cola_, vector<Cliente*> clientes_);

	void update() override;

	void render(SDL_Rect* cameraRect) override;

	bool collide(SDL_Rect rect) override;
	bool colisionClientes() override;

	void setState(EstadoClientes est);
	EstadoClientes getState();

	int numIntegrantes();
	vector<Cliente*> getIntegrantes();

	bool ratonEncima() override;
	
	void onObjectPicked() override;
	void onObjectDropped() override;

	bool canPick() override;

	void onDesactivate() override;

	void hacerPedido(int tamMesa);
	void decirPedidio();
};






