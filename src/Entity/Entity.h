#pragma once
#include <SFML/Graphics.hpp>
#include "SFML/System.hpp"
#include <iostream>
#include "Components/MovementComponent.h"


class Entity
{
private:
	void initVars();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;
	MovementComponent* movementComponent;
public:
	Entity();
	virtual ~Entity();

	/*Component Functions*/
	void CreateSprite(sf::Texture* texture);
	void CreateMovementComponent(float maxVelocity);

	void SetSprite(int width, int totalFrames, int frame);


	/*Functions*/
	virtual void SetPosition(const float x, const float y);
	virtual void Move(const float& dt, const float x, const float y);
	virtual void Update(const float& dt);
	virtual void Render(sf::RenderTarget* target);
};