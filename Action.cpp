#include "Action.h"
#include "Character.h"
#include "Status.h"

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
	case 8:
		return "protect";
	case 9:
		return "shell";
	default:
		return "nothing";
	}
};

void Action::CreateStatusEffects(Character* target)
{
	switch (effect)
	{
	case poisoned:
		target->addStatus(new Status("Poison", 3, 10, 0, 0));
		break;
	case sadness:
		target->addStatus(new Status("Sadness", 3, 0, 50, 50));
		break;
	case sleep:
		target->addStatus(new Status("Sleep", 3, 0, 100, 0));
		break;
	case frozen:
		target->addStatus(new Status("Frozen", 1, 0, 0, -50));
		break;
	case burning:
		target->addStatus(new Status("Burning", 1, 10, 0, 0));
		break;
	default:
		//no status effect
		break;
	}
	//nothing, normal, KO, poisoned, sadness, sleep, frozen, burning, protect, shell
}

bool Action::getRequiresTarget()
{
	return requiresTarget;
}