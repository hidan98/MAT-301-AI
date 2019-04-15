#include "Application.h"

#include <imgui.h>
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
	aiState = center;
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

	output = engine->getOutputVariable("outputVel");

	//output = engine->getOutputValue(0);
	/*engine->setName("Fuzzy car engine");

	displacement = new fl::InputVariable;
	displacement->setName("displacement");
	displacement->setRange(-800, 800);
	displacement->setEnabled(true);
	displacement->addTerm(new fl::Gaussian("left", 339.7, -800));
	displacement->addTerm(new fl::Gaussian("center", 339.7, 0));
	displacement->addTerm(new fl::Gaussian("right", 339.7, 800));
	engine->addInputVariable(displacement);


	velocity = new fl::InputVariable;
	velocity->setName("velocity");
	velocity->setRange(-1, 1);
	velocity->setEnabled(true);
	velocity->addTerm(new fl::Gaussian("left", 0.4247, -1));
	velocity->addTerm(new fl::Gaussian("straight", 0.4247, 0));
	velocity->addTerm(new fl::Gaussian("right", 0.4247, 1));
	engine->addInputVariable(velocity);

	output = new fl::OutputVariable;
	output->setName("output");
	output->setEnabled(true);
	output->setRange(-1, 1);
	output->setLockValueInRange(true);
	output->setAggregation(new fl::Maximum);
	output->setDefuzzifier(new fl::Centroid);
	output->setDefaultValue(fl::nan);
	output->setLockPreviousValue(false);
	output->addTerm(new fl::Triangle("hardLeft", -1.5, -1, -0.5));
	output->addTerm(new fl::Triangle("left", -1, -0.5, 0));
	output->addTerm(new fl::Triangle("noChange", -0.5, 0, 0.5));
	output->addTerm(new fl::Triangle("right", 0, 0.5, 1));
	output->addTerm(new fl::Triangle("hardRight", 0.5, 1, 1.5));
	engine->addOutputVariable(output);


	rules = new fl::RuleBlock;
	rules->setName("Rules");
	rules->setEnabled(true);
	rules->setConjunction(new fl::Minimum);
	rules->setDisjunction(fl::null);
	rules->setImplication(new fl::AlgebraicProduct);
	rules->setActivation(new fl::General);

	rules->addRule(fl::Rule::parse("if displacement is left and velocity is left then output is hardRight", engine));
	rules->addRule(fl::Rule::parse("if displacement is left and velocity is straight then output is right", engine));
	rules->addRule(fl::Rule::parse("if displacement is left and velocity is right then output is noChange", engine));

	rules->addRule(fl::Rule::parse("if displacement is center and velocity is left then output is right", engine));
	rules->addRule(fl::Rule::parse("if displacement is center and velocity is straight then output is noChange", engine));
	rules->addRule(fl::Rule::parse("if displacement is center and velocity is right then output is left", engine));

	rules->addRule(fl::Rule::parse("if displacement is right and velocity is left then output is noChange", engine));
	rules->addRule(fl::Rule::parse("if displacement is right and velocity is straight then output is left", engine));
	rules->addRule(fl::Rule::parse("if displacement is right and velocity is right then output is hardLeft", engine));
	engine->addRuleBlock(rules);

	std::string status;
	if (not engine->isReady(&status))
	{
		std::cout << status << std::endl;
		throw fl::Exception("[engine error] engine is not ready:n" + status, FL_AT);
	}
		*/
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
	if (raceLine->getPosition().x < 0)
	{
		raceLine->setPosition(0, raceLine->getPosition().y);
	}
	else if (raceLine->getPosition().x > screen.x)
	{
		raceLine->setPosition(screen.x, raceLine->getPosition().y -1);
	}
	//
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
	ImGui::Checkbox("Change Ai", &changeAI);

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
		aiState = center;
	}
	else if (car->getDisplacment().x > 0.2f && car->getDisplacment().x < 400)
	{
		aiState = right;
	}
	else if ((car->getDisplacment().x > 400))
	{
		aiState = farRight;
	}
	else if (car->getDisplacment().x < -0.2f && car->getDisplacment().x > -400)
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
		car->setVelocity(sf::Vector2f(1.0f, car->getVelocity().y));
		break;
	case left:
		car->setVelocity(sf::Vector2f(0.5f, car->getVelocity().y));
		break;

	case center:

		break;
	case right:
		car->setVelocity(sf::Vector2f(-0.50f, car->getVelocity().y));
		break;

	case farRight:
		car->setVelocity(sf::Vector2f(-1.0f, car->getVelocity().y));
		break;

	default:
		break;
	}
}