#include "Action.h"
#include "Character.h"
Action::Action(std::string newName, damageType newType)
	: name{newName}, type{newType}
{

}

std::string Action::getName()
{
	return name;
}
/*
void Action::useAction() {

}
*/

bool Action::getRequiresTarget()
{
	return requiresTarget;
}