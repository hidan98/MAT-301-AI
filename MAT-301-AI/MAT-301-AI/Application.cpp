#include "Application.h"



Application::Application(sf::RenderWindow* hwnd)
{
	window = hwnd;
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
