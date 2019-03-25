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

	setPosition(screen.x / 2, screen.y - 100);
	
	displacement = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);
	screen_ = screen;

	state = middle;
}

void Car::cleanUp()
{

}

void Car::update()
{
	displacement.x = getPosition().x - raceLine->getPosition().x;
	//std::cout << displacement.x << std::endl;
	

	findPositon();
	
}

sf::Vector2f Car::getDisplacment()
{
	displacement.x = getPosition().x - raceLine->getPosition().x;
	return displacement;
}

void Car::findPositon()
{
	float temp = (float)screen_.x *(1.f / 6.f);

	switch (state)
	{
	case middle:
		if (raceLine->getPosition().x < getPosition().x)
		{
			
			if (displacement.x > temp)
			{
				std::cout << "the line is far left of the car" << std::endl;
			}
		}
		else if (raceLine->getPosition().x > getPosition().x)
		{
			std::cout << "the line is right of the car" << std::endl;
		}

	default:
		break;
	}
	

	/*float temp1 = (-temp);
	if (raceLine->getPosition().x < getPosition().x)
	{
		

		if (displacement.x < temp)
		{
			

		}

		if (displacement.x < temp * 2)
		{
			std::cout << "The car is far left" << std::endl;
		}
	}
	else
	{
		std::cout << "the line is right of the car" << std::endl;
	}*/
}