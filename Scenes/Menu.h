#pragma once

#include "../Control/ObjectManager.h"
#include "../Scenes/Scene.h"

class Menu : public Scene
{
public:
	Menu(Game* game);
	~Menu();

	void render() override;
	void debug() override;
};