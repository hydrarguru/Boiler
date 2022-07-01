#pragma once
//#include "Core/boiler.h"
#include <SFML/Graphics.hpp>
#include "SFML/System.hpp"


class MovementComponent
{
private:
    float maxVelocity;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f deceleration;
	
public:
    MovementComponent(float maxVelocity);
    ~MovementComponent();

    float GetMaxVeloctity();
    sf::Vector2f& GetVelocity();
    sf::Vector2f& SetVelocity(float velocity);

    void Move(const float x, const float y);
    void Update(const float &dt);
};

