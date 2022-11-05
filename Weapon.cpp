#include "Weapon.h"

//Weapon::Weapon(){}

Weapon::Weapon(weaponType type, int attack, std::string name)
	: type{ type }, attack{ attack }, name { name }
{}

int Weapon::getAttack()
{
	return attack;
}

std::string Weapon::getName()
{
	return name;
}

Weapon::~Weapon()
{
	//std::cout << name << " destroyed.\n";
}