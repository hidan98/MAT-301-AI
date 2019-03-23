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

	engine = new fl::Engine;
	engine->setName("Fuzzy car engine");


	for (int i = 0; i < 6; i++)
	{
		float temp = (float)screen_.x *(1.f / 6.f);
		arrayOfLines[i].setSize(sf::Vector2f(1, screen.y));
		arrayOfLines[i].setPosition(sf::Vector2f(temp*(i + 1), 0));
		arrayOfLines[i].setFillColor(sf::Color::Red);
	}
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
	for (int i = 0; i < 6; i++)
	{
		window->draw(arrayOfLines[i]);
	}

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