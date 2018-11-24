#include "cState.h"

cState::cState(std::string name)
{
	_name = name;
}

void cState::CheckTransitionConditions()
{
	for (int i = 0; i < _transitions.size(); i++)
	{
		sTransition* t = &_transitions[i];

		if (_pMachine->StateExists(t->stateTo))
		{
			if (t->transitionCondition)
			{
				if (t->transitionCondition())
				{
					_pMachine->TriggerTransition(*t);
				}
			}
		}
		else
		{
			#ifdef __DEBUG___
				Serial.printf("STATE %s EXISTIERT NICHT\n", t->stateTo);
			#endif
		}
	}
}

void cState::AddTransition(sTransition t)
{
	_transitions.push_back(t);
}

void cState::SetStateMachine(cStateMachine * mach)
{
	_pMachine = mach;
}

std::string cState::GetName()
{
	return _name;
}
