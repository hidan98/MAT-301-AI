#include "Car.h"

#include <iostream>

Car::Car()
{
	raceLine = nullptr;
}


Car::~Car()
{
}

void Car::init(sf::RectangleShape* shape, sf::Vector2i screen)
{
	raceLine = shape;
	setSize(sf::Vector2f(40, 80));

	float x = getOrigin().x + (getLocalBounds().width / 2);
	float y = getOrigin().y + (getLocalBounds().height / 2);


	setOrigin(sf::Vector2f(x, y));

	setPosition(screen.x / 2, screen.y - 100);
	
	displacement = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);
	screen_ = screen;

}

void Car::cleanUp()
{

}

void Car::update()
{
	displacement.x = getPosition().x - raceLine->getPosition().x;
	move(velocity.x, 0);
	//std::cout << displacement.x << std::endl;

	
}


