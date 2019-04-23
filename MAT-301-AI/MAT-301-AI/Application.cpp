#include "Application.h"

//#include <imgui.h>
#include <imgui-SFML.h>
#include <string>


Application::Application(sf::RenderWindow* hwnd, Input* in, sf::Vector2i screen_)
{
	engine = nullptr;
	velocity = nullptr;
	displacement = nullptr;
	output = nullptr;
	window = hwnd;
	input = in;

	screen = screen_;
	//set up race line. No need for own class since it has a simple job
	raceLine = new sf::RectangleShape(sf::Vector2f(2, screen.y));
	raceLine->setPosition(screen.x /2, 0);
	raceLine->setFillColor(sf::Color::White);
	//set up car
	car = new Car;
	car->setVelocity(sf::Vector2f(0,0));
	car->init(raceLine, screen);	

	//set up fuzzylite
	setUpFUIS();

	aiState = centre;
	changeAI = false;


}

//cleans up on shut down
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
	//import FIS file
	engine = fl::FisImporter().fromFile("fuzzy.fis");

	//check if there any errors
	std::string status;
	if (not engine->isReady(&status))
		throw fl::Exception("[engine error] engine is not ready:\n" + status, FL_AT);

	//set up input variables
	displacement = engine->getInputVariable("Displacement");
	velocity = engine->getInputVariable("velocity");
	//setup output variable
	output = engine->getOutputVariable("outputVelocity");
}

void Application::handleInput()
{
	//check if arrow keys have been pressed to move line
	if (input->isKeyDown(sf::Keyboard::Right))
	{
		raceLine->setPosition(raceLine->getPosition().x + 1, 0);
	}
	if (input->isKeyDown(sf::Keyboard::Left))
	{
		raceLine->setPosition(raceLine->getPosition().x - 1, 0);
	}
}

//function used to check that the line cant move off the screen 
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
	//check that line is on screen
	lineCheck();

	//test mode used to test output data
	if (testMode)
	{
		//inputs from Dear ImGui
		fl::scalar inDis = inputDIsplacment;
		fl::scalar inVel = inputVelocity;
		//pass data into FIS
		displacement->setValue(inDis);
		velocity->setValue(inVel);
		//process the data in FIS
		engine->process();
	}
	else //non test mode
	{
		//cheks what state we are in, Primarly used for state machine but also to print to ImGui
		checkState();
		//selects ai technique. Starts with FIS
		if (changeAI)
		{
			stateMachine();
		}
		else
		{
			//inputs from car
			fl::scalar inputDis = car->getDisplacment().x;			
			fl::scalar inputVel = car->getVelocity().x;
			//pass data to engine
			displacement->setValue(inputDis);
			velocity->setValue(inputVel);
			//prosess data
			engine->process();
			//set new car velocity to the output of the engine
			car->setVelocity(sf::Vector2f(output->getValue(), car->getVelocity().y));
		}
		//update car
		car->update();
	}
	//update ImGui
	ImGui::SFML::Update(*window, sf::seconds(dt));
}

//draws graphics on screen
void Application::render()
{
	beginRender();
	window->draw(*raceLine);
	window->draw(*car);
	renderImGui();
	
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
//checks the current displacment and updates state based on it
void Application::checkState()
{
	//wil be classed as center if the car is inbetween -1 and 1. Due to it juttering this had been implemented
	if ((car->getDisplacment().x <1) && (car->getDisplacment().x > -1))
	{
		aiState = centre;
		stateString = "Center";
	}
	//another offset to stop juttering
	else if ((car->getDisplacment().x > 0.2f) && (car->getDisplacment().x < 400))
	{
		aiState = right;
		stateString = "Right";
	}
	else if ((car->getDisplacment().x > 400))
	{
		aiState = farRight;
		stateString = "Far Right";
	}
	//another offset to stop juttering
	else if ((car->getDisplacment().x < -0.2f) && (car->getDisplacment().x > -400))
	{
		aiState = left;
		stateString = "Left";
	}
	else if (car->getDisplacment().x < -400)
	{
		aiState = farLeft;
		stateString = "Far Left";
	}
}

//main state machine, check what state it is in and then adjust veocity
void Application::stateMachine()
{
	//cheks which state it is currenlty in and sets the velocity of the car
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

void Application::renderImGui()
{
	//local variable to hold state text
	const char* states[5] = { "Far Left", "Left", "Centre", "Right", "Far Right" };
	ImGui::Begin("Debug");
	ImGui::Text("Velocity of output FIS %f", output->getValue());
	ImGui::Text("Displacment %f", car->getDisplacment().x);
	ImGui::Text("ai state %s", states[aiState]);
	if (!changeAI)
	{
		ImGui::Text("Current Ai: FIS");
	}
	else
	{
		ImGui::Text("Current Ai: State Machine");
	}	
	ImGui::Checkbox("Change Ai", &changeAI);
	ImGui::Checkbox("Test Mode", &testMode);

	//will only activate when test mode is enabled
	if (testMode)
	{
		//allows user to input test data for the FIS
		ImGui::InputFloat("Velocity", &inputVelocity);
		ImGui::InputInt("Displacment", &inputDIsplacment);
		ImGui::Text("Output velocity: %f", output->getValue());
	}

	ImGui::End();
	ImGui::SFML::Render(*window);
}