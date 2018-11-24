#pragma once

#include <functional>
#include <string>

struct sTransition
{
	std::string stateFrom;
	std::string stateTo;
	std::function<bool()> transitionCondition;
	std::function<void()> transitionAction;
};