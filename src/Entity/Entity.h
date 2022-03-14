#pragma once
#include "Core/boiler.h"


class Entity
{
private:
	void initVars();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;

	float movementSpeed;
public:
	Entity();
	virtual ~Entity();

	/*Component Functions*/
	void CreateSprite(sf::Texture* texture);

	/*Functions*/
	virtual void SetPosition(const float x, const float y);
	virtual void Move(const float& dt, const float x, const float y);
	virtual void Update(const float& dt);
	virtual void Render(sf::RenderTarget* target);
};