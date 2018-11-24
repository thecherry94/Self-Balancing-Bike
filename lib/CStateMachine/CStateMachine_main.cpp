#include <iostream>
#include <string.h>

#include "CStateMachine.h"
#include "CState.h"

using namespace std;



class MyTestState : public CState
{
    private:
        bool _leave;
        bool _reallyLeave;

    public:
        MyTestState(const char* name, CStateMachine* stateMachine)
            : CState(name, stateMachine)
        {
            _leave = false;
            _reallyLeave = false;
        }

        void setupTransitions()
        {
            char* targetName;

            if(strcmp("1", GetName()) == 0)
            {
                targetName = "2";
            }
            else
            {
                targetName = "1";
            }

            AddTransition(
                targetName, 
                [&]() 
                {
                    // Transitionsbedingung
                    return _leave && _reallyLeave;
                },
                [&]()
                {
                    cout << "Transitioning... 1\n";
                });
        }

        void enter()
        {
            cout << "MyTestState::enter() 1\n";
        }

        void process()
        {
            cout << "MyTestState::enter() 1\n";

            if(!_leave)
            {
                while(true)
                {
                    cout << "Willst du diesen State verlassen? [y/n] ";

                    char in;
                    cin >> in;

                    if (in == 'y')
                    {
                        _leave = true;
                        break;
                    }
                    else continue;
                }
            }

            if(!_reallyLeave)
            {
                while(true)
                {
                    cout << "Wirklich verlassen?? :o [y/n] ";

                    char in;
                    cin >> in;

                    if (in == 'y')
                    {
                        _reallyLeave = true;
                        break;
                    }
                    else
                    {
                        _leave = false;
                        break;
                    }
                }
            }
        }

        void leave()
        {
            cout << "MyTestState::leave()\n";
        }
};


int main()
{
    CStateMachine states;

    MyTestState state1("1", &states);
    states.AddState(&state1);

    MyTestState state2("2", &states);
    states.AddState(&state2);

    while(true)
    {
        states.Update();
    }

    return 0;
}