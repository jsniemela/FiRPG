#pragma once
#include "Action.h"

class Skill: public Action
{
private:
	enum damageType { physical, healing, poison, fire, ice } dmgType;
	int baseDamage;
public:
	Skill();
	Skill(std::string newName);
	~Skill(){}
};