#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	/*Variables*/

	/*Initializer Functions*/
	void initVars();
	void initComponents();

public:
	Player(sf::Texture* texture, float x, float y);
	virtual ~Player();
	/*Functions*/
};

