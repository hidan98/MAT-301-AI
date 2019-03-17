#include "Application.h"

Application::Application(sf::RenderWindow* hwnd, Input* in, sf::Vector2i screen_)
{
	window = hwnd;
	input = in;

	screen = screen_;
	
	raceLine = new sf::RectangleShape(sf::Vector2f(2, screen.y));
	raceLine->setPosition(screen.x /2, 0);
	raceLine->setFillColor(sf::Color::White);

	car = new Car;
	car->init(raceLine, screen);	
}


Application::~Application()
{
}


void Application::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::Right))
	{
		
		raceLine->setPosition(raceLine->getPosition().x + 1, 0);
	}
	if (input->isKeyDown(sf::Keyboard::Left))
	{

		raceLine->setPosition(raceLine->getPosition().x - 1, 0);
	}
}

void Application::update(float dt)
{
	car->update();
}

void Application::render()
{
	beginRender();
	window->draw(*raceLine);
	window->draw(*car);


	endRender();
}

void Application::beginRender()
{
	window->clear(sf::Color::Black);
}

void Application::endRender()
{
	window->display();
}