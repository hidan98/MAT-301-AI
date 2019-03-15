#include "Application.h"



Application::Application(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	
	raceLine = new sf::RectangleShape(sf::Vector2f(2, 900));
	raceLine->setPosition(1600 / 2, 0);
	raceLine->setFillColor(sf::Color::White);
}


Application::~Application()
{
}


void Application::handleInput()
{

}

void Application::update(float dt)
{

}

void Application::render()
{
	beginRender();
	window->draw(*raceLine);


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
