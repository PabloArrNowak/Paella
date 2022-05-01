#include "Lobby.h"
#include "../Scenes/Jornada.h"
#include "../Scenes/Tutorial.h"
#include "../Control/NetworkManager.h"
#include "../GameObjects/UI/ShowText.h"
#include "../Scenes/HostClient.h"

Lobby::Lobby(Game* game) : Scene(game)
{
	//fondo
	fondo->setTexture("lobbyBg");
	fondo->setPosition(sdlutils().width() / 2, sdlutils().height() / 2);
	fondo->setDimension(sdlutils().width(), sdlutils().height()+100);

	//Cocinera
	Imagen* cocinera = new Imagen(game, sdlutils().width() / 2 - 300, sdlutils().height() / 2, 450, 450, "cocineraLobby");

	uiManager->addInterfaz(cocinera);

	//Nombre cocinera
	
	ShowText* NombreCocinera = new ShowText(game, game->getNombre(), "lobby",
		(int)cocinera->getX(), sdlutils().height()- 165);

	uiManager->addInterfaz(NombreCocinera);

	//Imagen del camarero conectandose
	camarero = new Imagen(game, sdlutils().width() / 2 + 300, sdlutils().height() / 2, 450, 450, "CamareroConect");

	uiManager->addInterfaz(camarero);

	//IP ??
	buscando = new ShowText(game, "ESPERANDO             JUGADORES...", "lobby", sdlutils().width() / 2+20, sdlutils().height() - 115);

	uiManager->addInterfaz(buscando);

	////Nombre del camarero
	//ShowText* NombreCamarero = new ShowText(game, "elvergalarga", "abadiNombre",
	//	(int)camarero->getX(), 100);

	//uiManager->addInterfaz(NombreCamarero);

	//Boton comenzar
	comenzar = new UiButton(game, "start2", sdlutils().width()/2, sdlutils().height()/2, 200, 70);
	comenzar->setInitialDimension(comenzar->getWidth(), comenzar->getHeight());
	comenzar->setAction([this](Game* game, bool& exit) {
		// crear player
		
		game->sendMessageScene(new Jornada(game, "Jornada1", 0 , true));

		sdlutils().virtualTimer().reset();
		// send info 
		game->getNetworkManager()->sendStartGame(0);
		uiManager->setEnJornada(true);
		});

	uiManager->addButton(comenzar);

	UiButton *regresar = new UiButton(game, "back", 100, 50, 125, 60);
	regresar->setInitialDimension(regresar->getWidth(), regresar->getHeight());
	regresar->setAction([](Game* game, bool& exit) {
		game->sendMessageScene(new HostClient(game));
		game->getNetworkManager()->close();
	});

	uiManager->addButton(regresar);

	uiManager->setEnLobby(true);
}

Lobby::Lobby(Game* game, string nombreHost) : Scene(game)
{
	//fondo
	fondo->setTexture("lobbyBg");
	fondo->setPosition(sdlutils().width() / 2, sdlutils().height() / 2);
	fondo->setDimension(sdlutils().width(), sdlutils().height()+100);

	//Cocinera
	Imagen* cocinera = new Imagen(game, sdlutils().width() / 2 - 300, sdlutils().height() / 2, 450, 450, "cocineraLobby");

	uiManager->addInterfaz(cocinera);

	//IP ??
	ShowText* listo = new ShowText(game, "LISTO PARA COMENZAR", "lobby", sdlutils().width() / 2, sdlutils().height() - 115);

	uiManager->addInterfaz(listo);

	//Nombre cocinera ? recibido de paquete
	ShowText* NombreCocinera = new ShowText(game, nombreHost, "ip",
		(int)cocinera->getX(), sdlutils().height() - 165);

	uiManager->addInterfaz(NombreCocinera);

	// Imagen del camarero conectandose 
	camarero = new Imagen(game, sdlutils().width() / 2 + 300, sdlutils().height() / 2, 450, 450, "camareroLobby");

	uiManager->addInterfaz(camarero);

	//Nombre del camarero ? tu propio nombre
	ShowText* NombreCamarero = new ShowText(game, game->getNombre(), "ip",
		(int)camarero->getX(), sdlutils().height() - 165);

	uiManager->addInterfaz(NombreCamarero);
}

void Lobby::clienteUnido(std::string nombreCliente)
{
	comenzar->setTexture("start");
	camarero->setTexture("camareroLobby");

	uiManager->setEnLobby(false);

	//Nombre del camarero
	ShowText* NombreCamarero = new ShowText(game, nombreCliente, "ip",
		(int)camarero->getX(), sdlutils().height() - 165);

	uiManager->addInterfaz(NombreCamarero);
	buscando->setText("LISTO PARA COMENZAR");

}
