#include "Player.h"

/*Initializer Functions*/
void Player::initVars()
{
	this->movementSpeed = 500;
	this->playerHealth = 100;
}

void Player::initComponents()
{
	
}

/*Construct/Deconstruct*/
Player::Player(sf::Texture* texture, float x, float y)
{
	this->initVars();
	this->initComponents();

	this->CreateSprite(texture);
	this->SetPosition(x, y);
}

Player::~Player()
{

}

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

