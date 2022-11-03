#include "Action.h"
#include "Character.h"

Action::Action()
{

}

Action::Action(std::string newName, DamageType newType)
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

std::string Action::getEffectName()
{
	std::string status = "";
	switch (effect) {
	case 0:
		return "nothing";
	case 1:
		return "status recovery";
	case 2:
		return "death";
	case 3:
		return "poison";
	case 4:
		return "sad";
	case 5:
		return "sleep";
	case 6:
		return "freeze";
	case 7:
		return "burn";
	default:
		return "nothing";
	}
};

bool Action::getRequiresTarget()
{
	return requiresTarget;
}