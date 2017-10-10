#include "InputHandler.h"


InputHandler::InputHandler()
{
	for (int i = 0; i < NUM_KEYS; i++)
		tapKey[i] = false;

	for (int i = 0; i < NUM_KEYS; i++)
	{
		this->stateCommands[i] = nullptr;
	}

}

InputHandler::~InputHandler()
{
}

void InputHandler::setCommand(KEY key, Command* command)
{
	this->stateCommands[key] = command;
}

void InputHandler::handleKeys()
{
	if (this->stateCommands[RIGHT] != nullptr)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !tapKey[RIGHT])
			this->stateCommands[RIGHT]->execute(tapKey[RIGHT]);
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && tapKey[RIGHT])
			tapKey[RIGHT] = false;
	}

	if (this->stateCommands[LEFT] != nullptr)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !tapKey[LEFT])
			this->stateCommands[LEFT]->execute(tapKey[LEFT]);
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && tapKey[LEFT])
			tapKey[LEFT] = false;
	}
}
