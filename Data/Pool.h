#pragma once
#include <vector>
#include <iostream>
#include <List>

#include "../GameObjects/Ingrediente.h"
#include "../GameObjects/Arroz.h"
#include "../Utils/Collider.h"

using namespace std;

class Game;

template<typename T>
class Pool
{
	Game* game;

	//lista con solo los objetos de la pool que est�n activos
	list<PoolObject*> activeObjects;

	//vector con toda la pool
	vector<T*> v;
	//numero de objetos en la Pool
	int numElems;
	//siguiente objeto a añadir al juego (o ultimo en haberse a�adido)
	int nextElem;

	void findNextElem() {
		nextElem = (nextElem + 1) % numElems;
		int cont = 0;

		//el bucle no itera ninguna vez en la mayor�a de casos, sobre todo en los ingredientes
		//(es posible que en el caso de los clientes o paellas tarde m�s en encontrar al siguiente)
		while (cont < numElems && v[nextElem]->isActive())
		{
			cont++;
			nextElem = (nextElem + 1) % numElems;
		}
		//si no encuentra ninguno, se duplica el tama�o de la pool
		if (cont == numElems) {
			for (int i = 0; i < numElems; i++)
				v.push_back(new T(game));
		
			numElems *= 2;

			while (cont < numElems && v[nextElem]->isActive())
			{
				cont++;
				nextElem = (nextElem + 1) % numElems;
			}		
		}
	}

public:
	Pool(Game* game, int n) : game(game), numElems(n), nextElem(-1) {
		for (int i = 0; i < n; i++)
			v.push_back(new T(game));
	}

	~Pool() {
		for (auto i : v) {
			delete i;
			i = nullptr;
		}
	};

	//metodo que busca el siguiente objeto y lo activa
	T* add(Vector2D<double> pos) {
		findNextElem();

		auto& elem = v[nextElem];
		activeObjects.push_front(elem);
		elem->setPosition(pos);
		elem->activate(activeObjects.begin());	

		return elem;
	}

	T* add() {
		findNextElem();

		auto& elem = v[nextElem];
		activeObjects.push_front(elem);
		elem->activate(activeObjects.begin());

		return elem;
	}

	//borra el objeto de la lista de activos
	void remove(list<PoolObject*>::const_iterator it) {
		(*it)->deactivate();
		activeObjects.erase(it);
	}

	vector<T*> getOverlaps(SDL_Rect GOcollider) {
		vector<T*> c;

		for (auto it : activeObjects) {
			if (it->overlap(GOcollider))
				c.push_back(dynamic_cast<T*>(it));
		}

		return c;
	}

	vector<T*> getCollisions(SDL_Rect GOcollider) {
		vector<T*> c;

		for (auto it : activeObjects) {
			if (it->collide(GOcollider))
				c.push_back(dynamic_cast<T*>(it));
		}

		return c;
	}

	void render() {	
		for (auto it : activeObjects)
			it->render();
	}

	void render(SDL_Rect* rect) {
		for (auto it : activeObjects)
			it->render(rect);
	}

	void debug() {
		for (auto it : activeObjects) {
			it->renderDebug();
		}
	}

	void debug(SDL_Rect* rect) {
		for (auto it : activeObjects) {
			it->renderDebug(rect);
		}
	}

	void update() {
		//Sacamos los objetos desactivados
		auto it = activeObjects.begin();
		while (it != activeObjects.end()) {
			if (!(*it)->isActive()) {
				it = activeObjects.erase(it);
			}
			else
				it++;
		}

		for (auto object : activeObjects) {
			object->update();
		}
	}
};



