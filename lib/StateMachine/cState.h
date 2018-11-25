#pragma once

#include <vector>

#include "etc.h"
#include "cStateMachine.h"


class cStateMachine;


class cState
{
	private:
		std::vector<sTransition> _transitions;
		std::string _name;

	protected:
		cState(std::string name);


	public:
		virtual void enter() = 0;
		virtual void process() = 0;
		virtual void leave() = 0;

		~cState();

		void CheckTransitionConditions();
		void AddTransition(sTransition);
		void SetStateMachine(cStateMachine* mach);

		cStateMachine* _pMachine;

		std::string GetName();

};