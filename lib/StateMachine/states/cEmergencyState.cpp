#include "cEmergencyState.h"


cEmergencyState::cEmergencyState(cBike* bike, std::string name)
    : cState(name)
{
    _bike = bike;
}


void cEmergencyState::enter()
{

}



void cEmergencyState::process()
{
    
}



void cEmergencyState::leave()
{
    
}