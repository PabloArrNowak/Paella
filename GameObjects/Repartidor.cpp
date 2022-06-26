#include "Repartidor.h"

#include "../Control/Game.h"
#include "../Control/ObjectManager.h"

#include "../GameObjects/ColaTakeaway.h"
#include "../Data/PedidoTakeaway.h"

#include "../../Data/Pedido.h"

#include "../GameObjects/Muebles/Mesa.h"

#include "../Scenes/Jornada.h"

Repartidor::Repartidor(Game* mGame) : GameObject(mGame), pedido(nullptr), cola(nullptr), estado_(repCAMINANDO)
{
	setDimension(DIMENSION, DIMENSION);

	setTexture("berenjena");


	texTolerancia = &sdlutils().images().at("barraTolerancia");
	tolerancia = 100;
	lastTimeTol = 0;

	showPed = false;
	orderStart = true;
	itemNow = 0;
	lastTimePed = 0;

	comidoMitad = false;
	lastTimeComido = 0;

	setDepth(3);
}

Repartidor::~Repartidor()
{
	sdlutils().soundEffects().at("conversacion2").haltChannel(canalSonido);
}

void Repartidor::init(ColaTakeaway* cola_)
{
	tolerancia = 100;

	posCola = cola_->getPos();
	cola = cola_;

	setVel(vel);

	estado_ = repCAMINANDO;
}

void Repartidor::update()
{
	if (estado_ == repCAMINANDO) {

		setPosition(pos + vel);
	}

	else if (estado_ == repENCOLA) {

		SDL_Rect col = getCollider();

		SDL_Rect rect = { col.x - col.w / 2, col.y - col.h, col.w, col.h };


		// Seguir cambiando
		colisionCartel();

		bajaTolerancia();
	}

	else if (estado_ == repESPERANDO) {

		if (!showPed)
			orderStart = true;

		bajaTolerancia();
	}

	else {
		bajaTolerancia();
	}
}

void Repartidor::render(SDL_Rect* cameraRect)
{
	int bocadilloX = 80;
	int bocadilloY = 80;

	if (showPed && estado_ == repESPERANDO) {
		if (sdlutils().virtualTimer().currTime() - lastTimePed >= PED_DELAY) {
			lastTimePed = sdlutils().virtualTimer().currTime();

			itemNow = (itemNow + 1) % texPedido.size();
		}

		int itemDim = 45;


		drawRender(cameraRect, { (int)getX() - bocadilloX / 2, (int)getY() - bocadilloY, bocadilloX, bocadilloY }, texTolerancia);
		drawRender(cameraRect, { (int)getX() - itemDim / 2, (int)getY() - 70, itemDim, itemDim }, &sdlutils().images().at(texPedido[itemNow]));

		showPed = false;
	}

	if (ratonEncima(cameraRect)) {

		SDL_Rect bocadillo = {};
		SDL_Rect emoticono = {};

		int emoticonoX = 35;
		int emoticonoY = 30;

		bocadillo = { bocadilloX / 2, (int)getOverlap().y - bocadilloY, bocadilloX, bocadilloY };
		emoticono = { emoticonoX / 2, (int)getOverlap().y - bocadilloY + emoticonoY / 2, emoticonoX, emoticonoY };

		drawRender(cameraRect, bocadillo, texTolerancia);
		drawRender(cameraRect, emoticono, &sdlutils().images().at(texturaTolerancia[((int)tolerancia / 20)]));
	}
}

bool Repartidor::colisionCartel()
{
	if (estado_ == repCAMINANDO)
		setState(repESPERANDO);

	return true;
}

bool Repartidor::ratonEncima(SDL_Rect* cameraRect)
{
	SDL_Rect rect = SDL_Rect();

	SDL_GetMouseState(&rect.x, &rect.y);
	rect = { rect.x + cameraRect->x,  rect.y + cameraRect->y, 5, 5 };

	return overlap(rect);
}

void Repartidor::bajaTolerancia()
{
	if (tolerancia > 0 && sdlutils().virtualTimer().currTime() - lastTimeTol >= DIMIN_TIME) {

		tolerancia -= DIMIN_TOLERANCIA;

		if (tolerancia < 0) tolerancia = 0;

		lastTimeTol = sdlutils().virtualTimer().currTime();
	}
}

void Repartidor::setState(EstadoRepartidor est)
{
	estado_ = est;

	lastTimeTol = sdlutils().virtualTimer().currTime();

	switch (estado_)
	{
	case repESPERANDO:
		para();
		break;
	case CAMINANDO:
		camina();
		break;
	default:
		break;
	}
}

EstadoRepartidor Repartidor::getState()
{
	return estado_;
}

void Repartidor::onDeactivate()
{
	setActive(false);
	// mesa->clienteSeVa();
	mGame->getCurrentScene()->addPuntuaciones(pedido->puntuarPedido(cajaTakeaway) * ((tolerancia + 50) / 100));
}

void Repartidor::hacerPedido(int tamMesa)
{
	if (estado_ != repCAMINANDO) {
		pedido = new PedidoTakeaway(mGame);

		texPedido = pedido->getPedidoTex();
	}
}

void Repartidor::modificaPedido(int numPaellas, vector<int> ingPedidos) {

	delete pedido; // borramos el anterior pedido
	pedido = new PedidoTakeaway(mGame, ingPedidos);

	texPedido = pedido->getPedidoTex();
}

void Repartidor::decirPedidio()
{
	if (estado_ == repESPERANDO) {
		if (orderStart) {
			lastTimePed = sdlutils().virtualTimer().currTime();
			itemNow = 0;
			orderStart = false;
		}
		showPed = true;
	}
}

void Repartidor::setOrientacion(bool vertical_)
{
	vertical = vertical_;
}

void Repartidor::para()
{
	// Ser�a para Anims
}

void Repartidor::camina()
{
	// Ser�a para Anims
}


