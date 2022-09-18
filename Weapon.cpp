#include "Weapon.h"

//Weapon::Weapon(){}

Weapon::Weapon(weaponType type, int attack, std::string name)
	: type{ type }, attack{ attack }, name { name }
{}

/*
Weapon::attachSkill(Skill weaponSkill)
{

}
*/