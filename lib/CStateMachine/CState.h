#ifndef STATE__H
#define STATE__H

#include <vector>
#include <map>
#include <functional>

#include "CStateMachine.h"

struct Transition
{ 
    char* targetStateName;
    std::function<bool()> transitionCondition;
    std::function<void()> transitionAction;
};

class CStateMachine;

class CState
{
    private:
        
        char* _name;
        std::map<const char*, std::vector<Transition>> _transitions;    // Transition von diesem State zu XYZ State Verhalten

    protected:
        CState(const char* name, CStateMachine* stateMachine);
        CStateMachine* _pStateMachine;
        void AddTransition(const char* targetStateName, std::function<bool()> transitionCondition, std::function<void()> transitionAction);

    public:        
        void CheckTransitionConditions();   // Überprüft, ob irgendwelche Bedingung für eine Transition erfüllt sind und ruft diese ggf. auf
        
        virtual void setupTransitions() = 0;
        virtual void process() = 0; // Wird bei jedem loop() Durchgang in der main aufgerufen
        virtual void enter() = 0;   // Wird immer aufgerufen, wenn dieser State betreten wird
        virtual void leave() = 0;   // Wird immer aufgerufen, wenn dieser State verlassen wird

        char* GetName()
        {
            return _name;
        }
};




#endif