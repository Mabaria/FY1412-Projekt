#pragma once
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "IInputHandler.h"

class InputHandler : public IInputHandler
{
private:
	bool tapKey[NUM_KEYS];
	Command* stateCommands[NUM_KEYS];

public:
	InputHandler();
	~InputHandler();

	void setCommand(KEY key, Command* command);
	void handleKeys();
};

#endif
