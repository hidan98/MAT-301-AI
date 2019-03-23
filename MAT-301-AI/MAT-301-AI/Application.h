#pragma once
#include <SFML\Graphics.hpp>
#include "Input.h"
#include "Car.h"
#include "fl/Headers.h"

class Application
{
public:
	Application(sf::RenderWindow* hwnd, Input* in, sf::Vector2i screen_);
	~Application();

	void handleInput();

	void update(float dt);

	void render();

private:

	void beginRender();
	void endRender();

	Input* input;
	sf::RenderWindow* window;

	sf::RectangleShape* raceLine;

	Car* car;

	sf::Vector2i screen;

	sf::RectangleShape arrayOfLines[6];

	fl::Engine* engine;
};

