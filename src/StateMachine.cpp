#include "StateMachine.h"

StateMachine::StateMachine() : currentState(nullptr)
{

}

StateMachine::~StateMachine()
{
	
}

void StateMachine::addState(std::string id, State* state)
{
	states.insert({ id, state });
}

State* StateMachine::getState(std::string id)
{
	return states[id];
}

void StateMachine::setCurrentState(std::string id)
{
	currentState = states[id];
}

State* StateMachine::getCurrentState()
{
	return currentState;
}
