#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	/*Variables*/
	int playerHealth;

	/*Initializer Functions*/
	void InitVariables();
	void InitComponents();

public:
	Player(sf::Texture* texture, float x, float y);
	virtual ~Player();
	/*Functions*/

	/*Getters/Setters*/
	int GetHealth();
	void SetPlayerHealth(int health);
	float GetPlayerVeloctity();
	void SetPlayerVelocity(float velocity);
};


