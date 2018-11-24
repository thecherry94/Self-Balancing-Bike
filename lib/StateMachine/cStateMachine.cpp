#include "cStateMachine.h"

void cStateMachine::Update()
{
	if (_pActiveState != nullptr)
	{
		_pActiveState->CheckTransitionConditions();
		_pActiveState->process();
	}
}

cStateMachine::cStateMachine()
{
	_pActiveState = nullptr;
	_pPreviousState = nullptr;
}

void cStateMachine::TriggerTransition(sTransition t)
{
	cState* current = _states[t.stateFrom];
	cState* next = _states[t.stateTo];



	current->leave();

	if (t.transitionAction)
		t.transitionAction();

	next->enter();



	_pActiveState = next;
	_pPreviousState = current;
}


bool cStateMachine::StateExists(std::string name)
{
	return _states.find(name) != _states.end();
}

void cStateMachine::AddState(cState * state)
{
	_states[state->GetName()] = state;
	state->SetStateMachine(this);

	if (_pActiveState == nullptr)
	{
		_pActiveState = state;
		_pActiveState->enter();
	}
}
