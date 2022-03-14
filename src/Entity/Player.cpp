#include "Player.h"

/*Initializer Functions*/
void Player::InitVariables()
{
	this->movementSpeed = 500;
	this->playerHealth = 100;
}

/*Construct/Deconstruct*/
Player::Player(sf::Texture* texture, float x, float y)
{
	this->InitVariables();
	this->CreateSprite(texture);
	this->SetPosition(x, y);
}

Player::~Player()
{

}

/*Getters & Setters*/
int Player::GetHealth()
{
	return this->playerHealth;
}

float Player::GetMovementSpeed()
{
	return this->movementSpeed;
}

void Player::SetSpeed(float speed)
{
	this->movementSpeed = speed;
	std::cout << "Set Player Speed: " << movementSpeed << std::endl;
}

void Player::SetPlayerHealth(int health)
{
	this->playerHealth = health;
	std::cout << "Set Player Health: " << playerHealth << std::endl;
}
