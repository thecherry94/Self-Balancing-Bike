#pragma once


#include "cState.h"

#include <map>

class cState;

class cStateMachine
{
	private:
		std::map<std::string, cState*> _states;
		cState* _pActiveState;
		cState* _pPreviousState;

	public:
		cStateMachine();
		void TriggerTransition(sTransition t);
		void Update();
		bool StateExists(std::string name);

		void AddState(cState* state);
};