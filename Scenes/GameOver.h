#pragma once

#include "../Scenes/Scene.h"

const vector<string> nombreTilemaps = { "jornada2", "restaurante", "restaurante", "restaurante",
	"restaurante", "restaurante" };

class GameOver : public Scene
{
public:
	GameOver(Game* game, int puntuacion,int numeroJornada);

private:
	int starNumber = 1;
	int nJornada = 0;
	int points = 0;
	int maxStars = 5; //maximo de estrellas
	int pointStarValue = 20; //num de puntos que vale una estrella
	
	Texture* starTexture;
		
	void calculateStarNumber();

	void render() override;

	std::vector<Texture*> m_reviews;
	void createRandomReviews();
	void renderReviews();
	int numStarsAdded = 0;

	void tweenEstrellas(vector<GameObject*> estrellas, int i = 0);
};

