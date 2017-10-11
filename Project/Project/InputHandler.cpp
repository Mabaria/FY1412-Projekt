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
	if (this->stateCommands[LEFT] != nullptr) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !tapKey[LEFT]) {
			this->stateCommands[LEFT]->execute(tapKey[LEFT]);
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && tapKey[LEFT]) {
			tapKey[LEFT] = false;
		}
	}

	if (this->stateCommands[RIGHT] != nullptr) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !tapKey[RIGHT]) {
			this->stateCommands[RIGHT]->execute(tapKey[RIGHT]);
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && tapKey[RIGHT]) {
			tapKey[RIGHT] = false;
		}
	}

	if (this->stateCommands[ENTER] != nullptr) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !tapKey[ENTER]) {
			this->stateCommands[ENTER]->execute(tapKey[ENTER]);
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && tapKey[ENTER]) {
			tapKey[ENTER] = false;
		}
	}

	if (this->stateCommands[A] != nullptr) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !tapKey[A]) {
			this->stateCommands[A]->execute(tapKey[A]);
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && tapKey[A]) {
			tapKey[A] = false;
		}
	}

	if (this->stateCommands[D] != nullptr) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !tapKey[D]) {
			this->stateCommands[D]->execute(tapKey[D]);
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && tapKey[D]) {
			tapKey[D] = false;
		}
	}

	if (this->stateCommands[SPACE] != nullptr) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !tapKey[SPACE]) {
			this->stateCommands[SPACE]->execute(tapKey[SPACE]);
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && tapKey[SPACE]) {
			tapKey[SPACE] = false;
		}
	}

	if (this->stateCommands[E] != nullptr) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !tapKey[E]) {
			this->stateCommands[E]->execute(tapKey[E]);
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && tapKey[E]) {
			tapKey[E] = false;
		}
	}

	if (this->stateCommands[RCTRL] != nullptr) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !tapKey[RCTRL]) {
			this->stateCommands[RCTRL]->execute(tapKey[RCTRL]);
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && tapKey[RCTRL]) {
			tapKey[RCTRL] = false;
		}
	}
}
