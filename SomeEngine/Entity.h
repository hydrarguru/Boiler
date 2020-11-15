#pragma once
#include "boiler.h"


class Entity
{
private:
protected:
	float movementSpeed;
	sf::CircleShape shape;
public:
	Entity();
	virtual ~Entity();

	/*Getters/Setters*/
	void setMovementSpeed(float speed) {
		movementSpeed = speed;
	}
	float getMovementSpeed() {
		return movementSpeed;
	}
	sf::CircleShape getPlayerShape(){
		return shape;
	}
	void setPlayerShapeColor(sf::Color color) {
		shape.setFillColor(color);
	}

	/*Functions*/
	virtual void Move(const float& dt, const float x, const float y);
	virtual void Update(const float& dt);
	virtual void Render(sf::RenderTarget* target);
};