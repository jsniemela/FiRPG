#include "Skill.h"
#include "Character.h"

Skill::Skill() 
{
	name = "Pass turn";
	baseDamage = 0;
	type = basic;
	statusProbability = 0;
	baseDamageDivider = 0;
	hpCostDivider = 0;
}

Skill::Skill(std::string newName, DamageType dmgType, bool req)
{
	name = newName;
	type = dmgType;
	requiresTarget = req;
	statusProbability = 0;
	baseDamageDivider = 0;
	hpCostDivider = 0;
}

Skill::Skill(std::string newName, int atk, int hp, DamageType dmgType)
	:baseDamage{atk}
{
	name = newName;
	requiresTarget = true;
	type = dmgType;
	statusProbability = 0;
	baseDamageDivider = 0;
	hpCostDivider = 0;
}

Skill::Skill(std::string newName, int atk, int hp, DamageType dmgType, bool req)
	:baseDamage{ atk }, hpCost{ hp }
{
	name = newName;
	type = dmgType;
	requiresTarget = req;
	baseDamageDivider = 0;
	hpCostDivider = 0;
}

Skill::Skill(std::string newName, int* atk, int* hp, int bdd, int hpcd, DamageType dmgType, bool req)
	:baseDamagePtr{ atk }, hpCostPtr{ hp }
{
	name = newName;
	type = dmgType;
	requiresTarget = true;
	baseDamageDivider = bdd;
	hpCostDivider = hpcd;
	requiresTarget = req;
}

Skill::Skill(std::string newName, int atk, int hp, DamageType dmgType, Effect eff, int statusProb, bool req)
	:baseDamage{ atk }, hpCost{hp}, statusProbability{ statusProb }
{
	name = newName;
	type = dmgType;
	requiresTarget = req;
	baseDamageDivider = 0;
	hpCostDivider = 0;
	effect = eff;
}

void Skill::useAction(Character* user, Character* target)
{
	if (type == analyze)
	{
		std::cout << "Target's weakness is " << target->getWeaknessName() << ".\n\n";
	}
	else {
		bool critical;
		int critrate = user->getCritRate();
		if (statusProbability != 0)
		{
			critrate = statusProbability; // replaces crit rate with statusProbability but still uses crit calculation
		}
		if (target->hasStatus("Sadness"))
		{
			critrate *= 2; // higher crit rate if target is sad
		}
		if (critrate > 100)
		{
			critrate = 100;
		}
		if (type == statusOnly)
		{
			std::cout << critrate << "/100 chance to apply status.\n";
		}
		else
		{
			std::cout << critrate << "/100 chance for critical attack.\n";
		}
		critical = critrate >= randomizeInt(1, 100); //true if critical
		if (type != statusOnly)
		{
			std::cout << user->getName() << " uses " << name << " on " << target->getName() << "!\n";
			int damage = calculateDamage(user->getAttack(), critical);
			target->takeDamage(damage, Character::physical, user);
		}
		if (effect != normal)
		{
			if (type == statusOnly)
			{
				std::cout << user->getName() << " tried to apply " << getEffectName() << " on " << target->getName() << "...\n";
				if (!critical)
				{
					std::cout << "and failed!\n\n";
				}
			}
			if (critical && effect != nothing)
			{
				CreateStatusEffects(target); 
			}
		}
		if (hpCost != 0)
		{
			user->takeDamage(hpCost, Character::ignoreDef, user);
		}
	}
}

int Skill::calculateDamage(int damage, bool crit) 
{
	int dmg = 0;
	int critBonus = 2;
	if (crit)
	{
		std::cout << "Critical Hit!\n";
		dmg = baseDamage + damage * critBonus;
	}
	else
	{
		dmg = baseDamage + damage;
	}
	return dmg;
}

void Skill::useAction(Character* user, std::vector<Character*> targets)
{
	if (type == basic)
	{
		user->guard();
	}
	else
	{
		int damage = user->getAttack();
		if (baseDamagePtr != nullptr)
		{
			if (baseDamageDivider != 0)
			{
				damage += *baseDamagePtr/baseDamageDivider;
			}
			else
			{
				damage += *baseDamagePtr;
			}
		}
		else {
			damage += baseDamage;
		}
		std::cout << user->getName() << " used " << name << "!\n";
		for (auto t : targets)
		{
			t->takeDamage(damage, Character::physical, user);
		}
		if (hpCost != 0 || hpCostPtr != nullptr)
		{
			if (hpCostPtr != nullptr)
			{
				if (baseDamageDivider != 0)
				{
					user->takeDamage(*hpCostPtr, Character::ignoreDef, user);
				}
				else
				{
					user->takeDamage(*hpCostPtr / hpCostDivider, Character::ignoreDef, user);
				}
			}
			else
			{
				user->takeDamage(hpCost, Character::ignoreDef, user);
			}
		}
	}
}

int Skill::getHPcost()
{
	if (hpCostPtr != nullptr)
	{
		return *hpCostPtr;
	}
	else {
		return hpCost;
	}
}

