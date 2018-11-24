/*
#include "CStateMachine.h"
#include "cTestState.h"

#include <iostream>

using namespace std;

int main()
{
	cStateMachine machine;

	cTestState state1("s1");
	cTestState state2("s2");

	bool switchState = false;

	sTransition t1_2;
	t1_2.stateFrom = "s1";
	t1_2.stateTo = "s2";
	t1_2.transitionAction = [&]() { cout << "Transition von 1 auf 2" << endl; switchState = false; };
	t1_2.transitionCondition = [&]() { return switchState; };

	sTransition t2_1;
	t2_1.stateFrom = "s2";
	t2_1.stateTo = "s1";
	t2_1.transitionAction = [&]() { cout << "Transition von 2 auf 1" << endl; switchState = false; };
	t2_1.transitionCondition = [&]() { return switchState; };

	state1.AddTransition(t1_2);
	state2.AddTransition(t2_1);

	machine.AddState(&state1);
	machine.AddState(&state2);

	while (true)
	{
		machine.Update();

		cout << "State �ndern? [y/n] ";
		char in;
		cin >> in;

		switch (in)
		{
			case 'y':
			case 'Y':
				switchState = true;
				break;
		}

		cout << endl;
	}

	return 0;
}
*/