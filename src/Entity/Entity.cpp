#include "Entity.h"

void Entity::initVars()
{
	this->texture = nullptr;
	this->sprite = nullptr;
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
	this->sprite->setTextureRect({0, 0, 64, 64});
	this->sprite->setScale(4.f, 4.f);
}

void Entity::CreateMovementComponent(float maxVelocity)
{
	this->movementComponent = new MovementComponent(maxVelocity);
}

void Entity::SetSprite(int width, int totalFrames, int frame)
{
	int i_frame = width / totalFrames;
	std::cout << "i_frame: " << i_frame << "\n";
	this->sprite->setTextureRect({frame * i_frame, 14, 64, 64});
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
	if (this->sprite && this->movementComponent)
	{
		this->movementComponent->Move(dir_x, dir_y);
		this->sprite->move(this->movementComponent->GetVelocity() * dt);
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
