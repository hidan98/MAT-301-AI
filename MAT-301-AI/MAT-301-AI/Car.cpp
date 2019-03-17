#include "Car.h"

#include <iostream>

Car::Car()
{
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

	std::cout << getOrigin().x << std::endl;
	std::cout << getOrigin().y << std::endl;

	setPosition(screen.x / 2, screen.y );
	
	displacement = sf::Vector2f(0, 0);
	screen_ = screen;

	state = middle;
}

void Car::cleanUp()
{

}

void Car::update()
{
	displacement.x = getPosition().x - raceLine->getPosition().x;
	std::cout << displacement.x << std::endl;
	findPositon();
	
}

void Car::findPositon()
{

	switch (state)
	{
	case middle:
		if()
	default:
		break;
	}
	float temp = (float)screen_.x *(1.f / 6.f);

	float temp1 = (-temp);
	if (raceLine->getPosition().x < getPosition().x)
	{
		

		if (displacement.x < temp)
		{
			std::cout << "the line is left of the car" << std::endl;

		}

		if (displacement.x < temp * 2)
		{
			std::cout << "The car is far left" << std::endl;
		}
	}
	else
	{
		std::cout << "the line is right of the car" << std::endl;
	}
}