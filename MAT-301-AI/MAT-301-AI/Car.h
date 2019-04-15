#pragma once
#include "SFML/Graphics.hpp"
class Car : public sf::RectangleShape
{

public:
	Car();
	~Car();
	void init(sf::RectangleShape* shape, sf::Vector2i screen);
	void update();

	void cleanUp();


	sf::Vector2f getDisplacment() { return displacement; }
	sf::Vector2f getVelocity() { return velocity; }
	void setVelocity(sf::Vector2f vel) { velocity = vel; }

private:

	sf::Vector2f velocity;

	sf::Vector2f displacement;

	sf::RectangleShape* raceLine;

	sf::Vector2i screen_;



};

