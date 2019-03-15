#include <sfml/Graphics.hpp>
#include "Input.h"
#include "Application.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "MAT 301");
	Input input;
	Application app(&window, &input);
	sf::Sprite;
	sf::Clock clock;
	float deltaTime;
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				input.setMousePos(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::KeyPressed:
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				input.setKeyUp(event.key.code);
				break;
			default:
				break;
			}
		}
		deltaTime = clock.restart().asSeconds();
		app.handleInput();
		app.update(deltaTime);
		app.render();
	

	}
	return 0;
}