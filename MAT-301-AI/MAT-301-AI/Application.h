#pragma once
#include <SFML\Graphics.hpp>
#include "Input.h"
#include "Car.h"
#include "fl/Headers.h"
#include <imgui.h>

enum state
{
	farLeft =0,
	left =1,
	centre =2,
	right = 3,
	farRight = 4
};

class Application
{
public:
	Application(sf::RenderWindow* hwnd, Input* in, sf::Vector2i screen_);
	~Application();

	void handleInput();

	void update(float dt);

	void render();

private:

	void beginRender();
	void endRender();

	void setUpFUIS();
	void stateMachine();
	void lineCheck();
	void checkState();
	void renderImGui();

	Input* input;
	sf::RenderWindow* window;

	sf::RectangleShape* raceLine;

	Car* car;

	sf::Vector2i screen;

	fl::Engine* engine;
	fl::InputVariable* displacement;
	fl::InputVariable* velocity;

	fl::OutputVariable* output;

	//fl::RuleBlock* rules;

	bool changeAI;
	bool testMode;
	float inputVelocity;
	int inputDIsplacment;

	state aiState;
	std::string stateString;

	ImGuiStyle style;

	const char* charArray;
};

