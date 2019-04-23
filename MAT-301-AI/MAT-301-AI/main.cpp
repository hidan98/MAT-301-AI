#include <sfml/Graphics.hpp>
#include "Input.h"
#include "Application.h"
#include "imgui.h"
#include "imgui-SFML.h"

int main()
{
	sf::Vector2i screen(1600, 900);
	//set upi sfml window
	sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), "MAT 301 AI");
	ImGui::SFML::Init(window);
	Input input;
	//send pointers to app
	Application app(&window, &input, screen);
	sf::Clock clock;
	float deltaTime;

	//main app loop
	while (window.isOpen())
	{
		sf::Event event;
		//process any events
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
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
		//update "game based stuff"
		app.handleInput();
		app.update(deltaTime);
		app.render();
	}

	ImGui::SFML::Shutdown();
	return 0;
}