#pragma once
#include <SFML\Graphics.hpp>
class Application
{
public:
	Application(sf::RenderWindow* hwnd);
	~Application();

	void handleInput();

	void update(float dt);

	void render();

private:

	void beginRender();
	void endRender();


	sf::RenderWindow* window;


};

