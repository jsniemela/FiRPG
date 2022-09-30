#include "Skill.h"
#include "Character.h"

Skill::Skill() 
{
	name = "Pass turn";
	baseDamage = 0;
	type = nothing;
}

Skill::Skill(std::string newName, bool req)
{
	name = newName;
	requiresTarget = req;
}

Skill::Skill(std::string newName, int atk, damageType damageType)
{
	name = newName;
	baseDamage = atk;
	type = damageType;
	requiresTarget = true;
}
/*
struct attack {
	int attack;
	enum status { normal, poisoned, KO, slow, haste, petrify, protect, shell } effect;
	enum damageType { physical, defensive, healing, poison, fire, ice } type;
};
*/

bool Skill::getRequiresTarget()
{
	return requiresTarget;
}


void Skill::useAction(Character* user, Character* target, int atk, int cr)
{
	bool critical;
	critical = cr >= randomizeInt(1, 100);

	float critBonus = 2.0f;
	std::cout << user->getName() << " attacks " << target->getName() << "!\n";
	if (critical)
	{
		std::cout << "Critical Hit!\n";
		//newAttack.attack = static_cast<float>(atk) * critBonus;
		//newAttack.effect = ;
		target->applyStatus(Character::poisoned); //apply poison on critical hit (for testing purposes)
		target->takeDamage(static_cast<float>(baseDamage + atk) * critBonus, Character::physical);
	}
	else
	{
		target->takeDamage(static_cast<float>(baseDamage + atk), Character::physical);
		//newAttack.attack = static_cast<float>(atk);
	}
}

void Skill::useAction(Character* user)
{
	user->guard();
}
