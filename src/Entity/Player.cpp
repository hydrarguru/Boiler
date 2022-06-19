#include "Player.h"

/*Initializer Functions*/
void Player::InitVariables()
{
	this->playerHealth = 100;
}

void Player::InitComponents()
{
	this->CreateMovementComponent(200.f);
}

/*Construct/Deconstruct*/
Player::Player(sf::Texture* texture, float x, float y)
{
	this->InitVariables();
	this->InitComponents();
	this->CreateSprite(texture);
	this->SetPosition(x, y);
}

Player::~Player()
{

}

/*Functions*/

/*Getters & Setters*/
int Player::GetHealth()
{
	return this->playerHealth;
}

void Player::SetPlayerHealth(int health)
{
	this->playerHealth = health;
	std::cout << "Set Player Health: " << playerHealth << std::endl;
}

float Player::GetPlayerVeloctity()
{
	return this->movementComponent->GetMaxVeloctity();
}

void Player::SetPlayerVelocity(float velocity)
{
	this->movementComponent->SetVelocity(velocity);
}