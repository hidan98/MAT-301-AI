#pragma once
#include <SFML\Graphics.hpp>
#include "Input.h"
class Application
{
public:
	Application(sf::RenderWindow* hwnd, Input* in);
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


};

