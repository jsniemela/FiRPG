#pragma once
#include <iostream>

class Weapon 
{
private:
	std::string name;
	int attack;
	//weapon should consist of 3 pieces: head, shaft, handle
	//parts of the weapon determine what skills can be used with it
public:
	enum weaponType { spear, sword, fists } type;
	Weapon(weaponType type, int attack, std::string name);
	int getAttack();
	std::string getName();
	//void attachSkill(Skill weaponSkill) // Create a skill class first
};