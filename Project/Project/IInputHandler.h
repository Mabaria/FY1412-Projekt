#pragma once
#ifndef IINPUTHANDLER_H
#define IINPUTHANDLER_H

#include "Command.h"
#include "SFML\Graphics.hpp"

enum KEY { D, A, SPACE, RIGHT, LEFT, ENTER, E, RCTRL };
const int NUM_KEYS = 8;

class IInputHandler
{
public:
	virtual void setCommand(KEY key, Command* command) = 0;
	virtual void handleKeys() = 0;
};

#endif
