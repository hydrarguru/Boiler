#include "Entity.h"

Entity::Entity()
{
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
	this->shape.setFillColor(sf::Color::White);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->Move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->Move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->Move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->Move(dt, 0.f, 1.f);
}

void Entity::Render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
