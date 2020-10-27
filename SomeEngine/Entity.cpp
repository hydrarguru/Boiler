#include "Entity.h"

Entity::Entity()
{
	this->shape.setPointCount(18);
	this->shape.setRadius(32.f);
	this->shape.setFillColor(sf::Color::Red);
	this->movementSpeed = 100.f;
}

Entity::~Entity()
{

}

void Entity::Move(const float& dt, const float dir_x, const float dir_y)
{
	this->shape.move(dir_x * movementSpeed * dt, dir_y * movementSpeed * dt);
}

void Entity::Update(const float& dt)
{
}

void Entity::Render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
