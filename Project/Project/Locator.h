#pragma once
#ifndef LOCATOR_H
#define LOCATOR_H

#include "IInputHandler.h"
#include "IGameTime.h"
#include "SFML\Graphics.hpp"

class Locator
{
private:
	static IInputHandler* sInput;
	static IGameTime* sGT;

public:
	static void provide(IInputHandler* input) { sInput = input; }
	static void provide(IGameTime* gameTime) { sGT = gameTime; }

	static IInputHandler* getInput() { return sInput; }
	static IGameTime* getGameTime() { return sGT; }
};

#endif
