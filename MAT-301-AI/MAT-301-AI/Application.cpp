#include "Application.h"

//#include <imgui.h>
#include <imgui-SFML.h>


Application::Application(sf::RenderWindow* hwnd, Input* in, sf::Vector2i screen_)
{
	engine = nullptr;
	velocity = nullptr;
	displacement = nullptr;
	output = nullptr;
	window = hwnd;
	input = in;

	screen = screen_;
	
	raceLine = new sf::RectangleShape(sf::Vector2f(2, screen.y));
	raceLine->setPosition(screen.x /2, 0);
	raceLine->setFillColor(sf::Color::White);

	car = new Car;
	car->setVelocity(sf::Vector2f(0,0));
	car->init(raceLine, screen);	

	setUpFUIS();
	aiState = centre;
	changeAI = false;


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
	engine->~Engine();
	delete engine;
	engine = nullptr;

	delete car;
	car = nullptr;

	delete raceLine;
	raceLine = nullptr;
}

void Application::setUpFUIS()
{
	engine = fl::FisImporter().fromFile("fuzzy.fis");

	std::string status;
	if (not engine->isReady(&status))
		throw fl::Exception("[engine error] engine is not ready:\n" + status, FL_AT);

	displacement = engine->getInputVariable("Displacement");
	velocity = engine->getInputVariable("velocity");

	output = engine->getOutputVariable("output1");

	
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

void::Application::lineCheck()
{
	if (raceLine->getPosition().x < 0)
	{
		raceLine->setPosition(0, raceLine->getPosition().y);
	}
	else if (raceLine->getPosition().x > screen.x)
	{
		raceLine->setPosition(screen.x, raceLine->getPosition().y - 1);
	}
}
void Application::update(float dt)
{
	lineCheck();

	if (testMode)
	{
		fl::scalar inDis = inputDIsplacment;
		fl::scalar inVel = inputVelocity;
		displacement->setValue(inDis);
		velocity->setValue(inVel);
		engine->process();
	}
	else
	{
		if (changeAI)
		{
			stateMachine();
		}
		else
		{
			fl::scalar temp = car->getDisplacment().x;
			displacement->setValue(temp);
			fl::scalar temp1 = car->getVelocity().x;
			velocity->setValue(temp1);
			engine->process();
			car->setVelocity(sf::Vector2f(output->getValue(), car->getVelocity().y));
		}


		car->update();
	}
	


	
	ImGui::SFML::Update(*window, sf::seconds(dt));
}

void Application::render()
{
	beginRender();
	window->draw(*raceLine);
	window->draw(*car);

	ImGui::Begin("dave");
	ImGui::Text("%f", output->getValue());
	ImGui::Text("Displacment %f", car->getDisplacment());
	ImGui::Text("ai state %i", aiState);
	ImGui::Checkbox("Test Mode", &testMode);
	ImGui::Checkbox("Change Ai", &changeAI);

	if (testMode)
	{
		ImGui::InputFloat("Velocity", &inputVelocity);
		ImGui::InputInt("Displacment", &inputDIsplacment);
		ImGui::Text("Output velocity: %f", output->getValue());
	}


	ImGui::End();
	ImGui::SFML::Render(*window);
	
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

void Application::checkState()
{
	if ((car->getDisplacment().x <1) && (car->getDisplacment().x > -1))
	{
		aiState = centre;
	}
	else if ((car->getDisplacment().x > 0.2f) && (car->getDisplacment().x < 400))
	{
		aiState = right;
	}
	else if ((car->getDisplacment().x > 400))
	{
		aiState = farRight;
	}
	else if ((car->getDisplacment().x < -0.2f) && (car->getDisplacment().x > -400))
	{
		aiState = left;
	}
	else if (car->getDisplacment().x < -400)
	{
		aiState = farLeft;
	}
}
void Application::stateMachine()
{
	checkState();

	switch (aiState)
	{
	case farLeft:
		car->setVelocity(sf::Vector2f(1.0f, 0));
		break;
	case left:
		car->setVelocity(sf::Vector2f(0.5f, 0));
		break;

	case centre:
		car->setVelocity(sf::Vector2f(0, 0));
		break;
	case right:
		car->setVelocity(sf::Vector2f(-0.50f, 0));
		break;

	case farRight:
		car->setVelocity(sf::Vector2f(-1.0f, 0));
		break;

	default:
		break;
	}
}