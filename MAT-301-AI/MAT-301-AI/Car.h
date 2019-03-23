#pragma once
#include "SFML/Graphics.hpp"
class Car : public sf::RectangleShape
{

	enum distance
	{
		farLeft,
		left,
		middle,
		right,
		farRight
	};
public:
	Car();
	~Car();
	void init(sf::RectangleShape* shape, sf::Vector2i screen);
	void update();

	void cleanUp();

	void findPositon();

private:

	sf::Vector2f velocity;

	sf::Vector2f displacement;

	distance state;

	sf::RectangleShape* raceLine;

	sf::Vector2i screen_;



};

