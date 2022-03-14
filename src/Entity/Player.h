#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	/*Variables*/
	int playerHealth;

	/*Initializer Functions*/
	void InitVariables();

public:
	Player(sf::Texture* texture, float x, float y);
	virtual ~Player();
	/*Functions*/

	/*Getters/Setters*/
	int GetHealth();
	float GetMovementSpeed();
	void SetSpeed(float speed);
	void SetPlayerHealth(int health);
};


