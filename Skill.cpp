#include "Skill.h"

Skill::Skill() 
{
	baseDamage = 0;
	dmgType = physical;
}

Skill::Skill(std::string newName)
{
	name = newName;
	baseDamage = 0;
	dmgType = physical;
}