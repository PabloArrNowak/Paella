#include "Pedido.h"
Pedido::Pedido(int numComensales, int numeroTiles)
{
	comensales = numComensales;
	tilesMesa = numeroTiles;

	ingredientesPedidos = vector<bool>(tipoIngrediente::LAST, false);
	TipoPaella tamano;
	int suma_tamanos = 0;
	tipoIngrediente ingredienteRand;
	if (comensales <= LIMITE_TAMANO) {
		max_rand = comensales;
	}
	else {
		max_rand = LIMITE_TAMANO;
	}

	for (int i = 0; i < tilesMesa && !tamanos_escogidos; i++)
	{
		int tamano_elegido;
		if ((0 < comensales <= 3) && (tilesMesa == 1)) {
			int t = comensales;
			tamano = TipoPaella(t - 1);
			tamano_elegido = t;
		}
		else {
			int t_random = rand() % max_rand + 1;
			tamano = TipoPaella(t_random - 1);
			tamano_elegido = t_random;
		}
		suma_tamanos += tamano_elegido;

		//explorar la posibiidad de crear un min rand en funcion del numero de tiles
		//explorar la posibilidad de un while(con el for dentro) en funcion de si tamano escogida
		//y tamanoescogida variarlo fuera del for en un if
		if (suma_tamanos > comensales) {
			suma_tamanos -= tamano_elegido;
			i--;
		}
		else if (suma_tamanos < comensales) {
			pedidoPaella nuevaPaella;
			paellas.push_back(nuevaPaella);
			paellas[i].tamanoPaella = tamano;
		}
		else if (suma_tamanos == comensales) {
			pedidoPaella nuevaPaella;
			paellas.push_back(nuevaPaella);
			paellas[i].tamanoPaella = tamano;
			tamanos_escogidos = true;
		}
	}
	for (int g = 0; g < paellas.size(); g++) {
		int c = rand() % LIMITE_INGR + 0;
		for (int j = 0; j < c; j++) {
			int n = rand() % (tipoIngrediente::LAST);
			ingredienteRand = tipoIngrediente(n);
			if (paellas[g].ingredientesPedido.size() < LIMITE_INGR && !ingredientesPedidos[ingredienteRand])
			{
				paellas[g].ingredientesPedido.push_back(ingredienteRand);
				ingredientesPedidos[ingredienteRand] = true;
			}
			else
			{
				j--;
			}
		}
		ingredientesPedidos = vector<bool>(tipoIngrediente::LAST, false);
	}
}
vector<pedidoPaella> Pedido::getPedido()
{
	return paellas;
}

void Pedido::puntuarPedido(vector<Paella*> comanda)
{

	//quitar pedido ->
	penalizacionTamano valorarT;
	penalizacionIngredientes valorarI;
	penalizacionCoccion valorarC;
	
	for (int i = 0; i < getPedido().size(); i++) {

		//Variar puntuacion en funcion de la diferencia de tama�os

		int tamanoPaella1 = int(getPedido()[i].tamanoPaella +1);
		int tamanoPaella2 = int(comanda[i]->getTipo() + 1);
		int diferencia = tamanoPaella1 - tamanoPaella2;
		switch (diferencia) {
		case 2:
			variarPuntuacion(valorarT.pequenaDos);
			break;
		case 1:
			variarPuntuacion(valorarT.pequenaUno);
			break;
		case -2:
			variarPuntuacion(valorarT.grandeDos);
			break;
		case -1:
			variarPuntuacion(valorarT.grandeUno);
			break;
		default:
			break;
		}

		//Variar puntuacion en funcion de la coccion de la paella.

		switch (comanda[i]->getResultado()) {
		case Cruda:
			variarPuntuacion(valorarC.cruda);
			break;
		case PocoHecha:
			variarPuntuacion(valorarC.pocoHecha);
			break;
		case Perfecta:
			variarPuntuacion(valorarC.perfecta);
			break;
		case MuyHecha:
			variarPuntuacion(valorarC.muyHecha);
			break;
		case Quemada:
			variarPuntuacion(valorarC.quemada);
			break;
		case Incomestible:
			variarPuntuacion(valorarC.incomestible);
			break;
		}

		//Variar puntuaciones en funcion de la diferencia de ingredientes.

		int cantidadIngr1 = int(getPedido()[i].ingredientesPedido.size());;
		int cantidadIngr2 = int(comanda[i]->getVIngredientes().size());
		int difCantidad = cantidadIngr2 - cantidadIngr1;
		if (difCantidad >= 0) {
			variarPuntuacion(valorarI.sobraIngr *difCantidad);
		}

		//Variar puntuaciones en funcion de los ingredientes que no se han cocinado.

		for (int j = 0; j < getPedido()[i].ingredientesPedido.size(); j++) {
			if (!comanda[i]->getIngrPaella()[getPedido()[i].ingredientesPedido[j]]) {
				variarPuntuacion(valorarI.faltaIngr);
			}
		}
	}	

	cout << puntuacion << endl;
}




void Pedido::variarPuntuacion(int variacion)
{
	puntuacion += variacion;
}

vector<string> Pedido::getPedidoTex()
{
	vector<string> v;

	for (auto i : paellas) {
		v.push_back(paellasTamTex[i.tamanoPaella]);
		for (auto j : i.ingredientesPedido) {
			v.push_back(paellasTex[j]);
		}
	}

	return v;
}