#include "Player.h"

/*Initializer Functions*/
void Player::initVars()
{

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