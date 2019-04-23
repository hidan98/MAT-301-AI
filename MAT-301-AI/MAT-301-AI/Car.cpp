#include "Car.h"

#include <iostream>

Car::Car() : raceLine(nullptr)
{
}


Car::~Car()
{
}

void Car::init(sf::RectangleShape* shape, sf::Vector2i screen)
{
	//used to calculate displacment in update
	raceLine = shape;
	//set size of car
	setSize(sf::Vector2f(40, 80));
	//re position the origin so its the center of the car
	float x = getOrigin().x + (getLocalBounds().width / 2);
	float y = getOrigin().y + (getLocalBounds().height / 2);
	setOrigin(sf::Vector2f(x, y));

	//set car to center of screen
	setPosition(screen.x / 2, screen.y - 100);
	
	displacement = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);

}


void Car::update()
{
	//calcualte displacement
	displacement.x = getPosition().x - raceLine->getPosition().x;
	//moves car
	move(velocity);
}


