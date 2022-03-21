#include "Ingredientebutton.h"
#include "../UI/UIManager.h"
Ingredientebutton::Ingredientebutton(UIManager* uim, Game* game, string texturename, int x, int y, int w, int h) : UiButton(game, texturename, x, y, w, h)
{
	this->uim = uim;
}
Ingredientebutton::~Ingredientebutton()
{
}
void Ingredientebutton::execute()
{
	uim->getComanda()->aņadiraPedido(textura);
	uim->randomizaTeclado();

	//Sonido de escribir aleatorio
	sdlutils().soundEffects().at("escribir" + std::to_string(sdlutils().rand().nextInt(2, 5))).play(0, game->UI);

	//comandat->aņadiraPedido(textuname);
	//HAY QUE CORTAR EL BUCLE DE INTERAZ AQUI POR QEU SI NO SE AŅADEN 6 INGREDIENTES AL PULDSAR UN BOTON XD
	//well podria ser un while en ligar d eun for
}
void Ingredientebutton::update()
{
}
