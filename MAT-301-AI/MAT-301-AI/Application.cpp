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

void Application::setUpFUIS()
{
	engine = new fl::Engine;
	engine->setName("Fuzzy car engine");

	displacement = new fl::InputVariable;
	displacement->setName("displacement");
	displacement->setRange(-800, 800);
	displacement->setEnabled(true);
	displacement->addTerm(new fl::Gaussian("left", 169.9, -400));
	displacement->addTerm(new fl::Gaussian("center", 169.9, 0));
	displacement->addTerm(new fl::Gaussian("right", 169.9, 400));
	displacement->setLockValueInRange(true);
	engine->addInputVariable(displacement);


	velocity = new fl::InputVariable;
	velocity->setName("velocity");
	velocity->setRange(-800, 800);
	velocity->setEnabled(true);
	velocity->addTerm(new fl::Gaussian("left", 0.4246, -1));
	velocity->addTerm(new fl::Gaussian("straight", 0.4246, 0.5));
	velocity->addTerm(new fl::Gaussian("right", 0.4246, 1));
	velocity->setLockValueInRange(true);
	engine->addInputVariable(velocity);

	output = new fl::OutputVariable;
	output->setName("output");
	output->setEnabled(true);
	output->setLockValueInRange(false);
	output->setAggregation(new fl::Maximum);
	output->setDefuzzifier(new fl::Centroid(100));
	output->setDefaultValue(fl::nan);
	output->setLockPreviousValue(false);
	//output->addTerm(new fl::)




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