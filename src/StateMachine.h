#pragma once
#include <map>
#include <string>

#include "State.h"

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void addState(std::string id, State* state);
	State* getState(std::string id);

	void setCurrentState(std::string id);
	State* getCurrentState();

private:
	std::map<std::string, State*> states;
	State* currentState;
};

