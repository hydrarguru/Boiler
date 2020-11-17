#include "Entity.h"

void Entity::initVars()
{
	this->texture = nullptr;
	this->sprite = nullptr;
	this->movementSpeed = 100.f;
}

Entity::Entity()
{
	this->initVars();
}

Entity::~Entity()
{
	delete this->sprite;
}

/*Component Functions*/
void Entity::CreateSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
	this->sprite->setTexture(*this->texture);
}



/*Functions*/
void Entity::SetPosition(const float x, const float y)
{
	if (this->sprite)
	{
		this->sprite->setPosition(x, y);
	}
}

void Entity::Move(const float& dt, const float dir_x, const float dir_y)
{
	if (this->sprite)
	{
		this->sprite->move(dir_x * movementSpeed * dt, dir_y * movementSpeed * dt);
	}
}

void Entity::Update(const float& dt)
{
}

void Entity::Render(sf::RenderTarget* target)
{
	if(this->sprite)
		target->draw(*this->sprite);
}
