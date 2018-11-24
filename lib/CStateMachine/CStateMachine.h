#ifndef STATEMACHINE__H
#define STATEMACHINE__H


#include <map>

#include "CState.h"

class CState;

class CStateMachine
{
    private:
        std::map<const char*, CState*> _states;
        CState* _pActiveState;


    public:
        CStateMachine();

        void AddState(CState* state);
        void SetState(const char* stateName);
        CState* GetState(const char* stateName);
        void Update();

};




#endif