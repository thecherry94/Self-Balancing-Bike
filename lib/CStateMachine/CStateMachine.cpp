#include "CStateMachine.h"
#include "CState.h"


CStateMachine::CStateMachine()
{

}

void CStateMachine::AddState(CState* state)
{
    _states[state->GetName()] = state;
}


void CStateMachine::SetState(const char* stateName)
{
    _pActiveState = _states[stateName];
}


CState* CStateMachine::GetState(const char* stateName)
{
    return _states[stateName];
}


void CStateMachine::Update()
{
    if(_pActiveState != nullptr)
    {
        _pActiveState->CheckTransitionConditions();
        _pActiveState->process();
    }
}