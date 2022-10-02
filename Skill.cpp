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

Skill::Skill(std::string newName, int atk, damageType dmgType)
{
	name = newName;
	baseDamage = atk;
	type = dmgType;
	requiresTarget = true;
}

Skill::Skill(std::string newName, int atk, damageType dmgType, status eff)
{
	name = newName;
	baseDamage = atk;
	type = dmgType;
	requiresTarget = true;
	effect = eff;
}

bool Skill::getRequiresTarget()
{
	return requiresTarget;
}

std::string Skill::getEffectName() {
	std::string status = "";
	switch (effect) {
	case 0:
		return "status recovery";
	case 1:
		return "poison";
	case 2:
		return "death";
	default:
		return "status recovery";
	}
};

void Skill::useAction(Character* user, Character* target, int atk, int cr)
{
	if (type != statusOnly) {
		bool critical;
		critical = cr >= randomizeInt(1, 100); //true if critical
		std::cout << user->getName() << " uses " << name << " on " << target->getName() << "!\n";
		float damage = calculateDamage(atk, critical);
		target->takeDamage(damage, Character::physical);
	}
	if (effect != normal) { 
		if (type == statusOnly) {
			std::cout << user->getName() << " tried to apply " << getEffectName() << " on " << target->getName() << "...\n";
		}
		target->applyStatus(static_cast<Character::status>(effect));
	}
}

float Skill::calculateDamage(float damage, bool crit) {
	float dmg = 0;
	float critBonus = 2.0f;
	if (crit)
	{
		std::cout << "Critical Hit!\n";
		dmg = static_cast<float>(baseDamage + damage) * critBonus;
	}
	else
	{
		dmg = static_cast<float>(baseDamage + damage);
	}
	return dmg;
}

void Skill::useAction(Character* user)
{
	user->guard();
}
