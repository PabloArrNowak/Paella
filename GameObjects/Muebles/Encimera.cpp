#include "Encimera.h"
#include "../Ingrediente.h"
#include "../Player.h"
#include "../Paella.h"

Encimera::Encimera(Game* game, Vector2D<double> pos) : Mueble(game, pos, 1 * TILE_SIZE, 2 * TILE_SIZE, "encimera")
{
}

bool Encimera::receiveIngrediente(Ingrediente* ingr)
{
	//Si ya tiene objeto, no recoge objeto
	if (ingr_ == nullptr && paella_ == nullptr)
	{
		ingr_ = ingr;

		ingr_->setPosition(getX(), getY());

		return true;
	}
	else
		return false;
}

bool Encimera::receivePaella(Paella* pa)
{
	//Si ya tiene objeto, no recoge objeto
	if (ingr_ == nullptr && paella_ == nullptr)
	{
		paella_ = pa;

		paella_->setPosition(getX(), getY());

		return true;
	}
	else
		return false;
}

bool Encimera::returnObject(Player* p)
{
	if (ingr_ != nullptr)
	{
		//TOCHECK: Podr�amos hacer un return del objeto y que el player se lo guarde a s� mismo
		p->setPickedObject(ingr_, INGREDIENTE);

		ingr_ = nullptr;

		return true;
	}
	else if (paella_ != nullptr)
	{
		p->setPickedObject(paella_, PAELLA);

		paella_ = nullptr;

		return true;
	}
	else
		return false;
}
