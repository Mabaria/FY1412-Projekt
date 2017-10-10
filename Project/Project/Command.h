#pragma once
#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
	// Executes the input and tapKey should be set to true if command is to only be fired once
	virtual void execute(bool &tapKey) = 0;
};

#endif
