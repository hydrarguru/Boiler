#include "MovementComponent.h"

MovementComponent::MovementComponent(float maxVelocity)
{
    this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}

float MovementComponent::GetMaxVeloctity()
{
    return this->maxVelocity;
}

sf::Vector2f& MovementComponent::GetVelocity()
{
    return this->velocity;
}

sf::Vector2f& MovementComponent::SetVelocity(float velocity)
{
    this->maxVelocity = velocity;
}

void MovementComponent::Move(const float dir_x, const float dir_y)
{
    this->velocity.x = this->maxVelocity * dir_x;
    this->velocity.y = this->maxVelocity * dir_y;
}

void MovementComponent::Update(const float &dt)
{

}