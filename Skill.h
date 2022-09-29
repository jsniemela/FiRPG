#pragma once
#include "Action.h"

class Skill: public Action
{
private:
	enum damageType { physical, poison, fire, ice } dmgType;
	int baseDamage;
public:
	Skill();
	~Skill(){}
};