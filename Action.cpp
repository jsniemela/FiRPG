#include "Action.h"

Action::Action(std::string newName)
	: name{ newName }
{
	
}

std::string Action::getName()
{
	return name;
}