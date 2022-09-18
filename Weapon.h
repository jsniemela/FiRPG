#pragma once
#include <iostream>

class Weapon 
{
private:
	std::string name;
	int attack;
	enum weaponType { spear, sword, fists } type;
	//weapon should consist of 3 pieces: head, shaft, handle
	//parts of the weapon determine what skills can be used with it
public:
	Weapon(weaponType type, int attack, std::string name);
	//void attachSkill(Skill weaponSkill) // Create a skill class first
};