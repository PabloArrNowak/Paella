#include "Paella.h"
#include "../sdlutils/SDLUtils.h"

Paella::Paella(Tama�o tama�o_):ObjetoPortable() , tama�o(tama�o_)
{

	setPosition(sdlutils().width() / 2, 100);
	setDimension(100, 100);

	setTexture("barraTolerancia");

	switch (tama�o)
	{
	case Mediana:
		sumaIntervalo = 5000;
		break;
	case Grande:
		sumaIntervalo = 10000;
		break;
	default:
		break;
	}
}

void Paella::a�adeIngr(Ingrediente ingr_)
{
	if (ingredientes.size() < MAX_INGR) ingredientes.push_back(ingr_);
}

void Paella::setState(Estado estado_)
{
	estado = estado_;
	tiempo = sdlutils().currRealTime();
}

void Paella::update()
{
	switch (estado)
	{
	case Preparacion:

		break;
	case Coccion:

		if (i < tiemposDeCoccion.size()) {
			if (sdlutils().currRealTime() - tiempo > tiemposDeCoccion[i]) {
				tiempo = tiemposDeCoccion[i];
				i++;
				estadoFinal = Resultado(i);
			}
		}

		break;
	case Preparada:
		break;
	}

	cout << "Estado actual: " << estadoFinal;
}

Estado Paella::getState()
{
	return estado;
}
