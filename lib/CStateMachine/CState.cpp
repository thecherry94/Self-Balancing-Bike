#include "CState.h"
#include "CStateMachine.h"


CState::CState(const char* name, CStateMachine* stateMachine)
{
    _name = (char*)name;
    _pStateMachine = stateMachine;
}


void CState::AddTransition(
    const char* targetStateName, 
    std::function<bool()> transitionCondition, 
    std::function<void()> transitionAction)
{
    Transition tran;
    tran.targetStateName = (char*)targetStateName;
    tran.transitionCondition = transitionCondition;
    tran.transitionAction = transitionAction;

    _transitions[targetStateName].push_back(tran);
}

void CState::CheckTransitionConditions()
{
    // Iterator für Transition-Map
    std::map<const char*, std::vector<Transition>>::iterator it;

    // Map durchgehen
    for(it = _transitions.begin(); it != _transitions.end(); it++)
    {
        // Für jedes gemappte Element ist ein vector hinterlegt

        // Iterator für Vector
        std::vector<Transition>& tranList = it->second;
        
        // Vector durchgehen
        for(int i = 0; i < tranList.size(); i++)
        {
            // Transition als Referenz
            Transition& tran = tranList[i];

            // Transitionsbedingungen erfüllt?
            if(tran.transitionCondition())
            {
                // Verlassen aufrufen
                leave();

                // Transitionsaktion aufrufen
                tran.transitionAction();

                // Aktuellen State wechseln
                _pStateMachine->SetState(tran.targetStateName);

                // Neuer, akuteller State enter aufrufen
                _pStateMachine->GetState(tran.targetStateName)->enter();
            }
        }
    }
}