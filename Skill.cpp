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
	case 3:
		return "sad";
	default:
		return "status recovery";
	}
};

void Skill::useAction(Character* user, Character* target, int atk, int cr)
{
	bool critical;
	int critrate = cr;
	if (type == statusOnly) {
		critrate *= 2; // double chance for status if skill doesn't apply damage.
	}
	if (target->getStatus() == static_cast<Character::status>(sadness)) {
		critrate *= 2; // double crit rate if target is sad
	}
	if (critrate > 100)
	{
		critrate = 100;
	}
	std::cout << critrate << "/100 chance for critical attack.\n";
	critical = critrate >= randomizeInt(1, 100); //true if critical
	if (type != statusOnly) {
		std::cout << user->getName() << " uses " << name << " on " << target->getName() << "!\n";
		float damage = calculateDamage(atk, critical);
		target->takeDamage(damage, Character::physical);
	}
	if (effect != normal) { 
		if (type == statusOnly) {
			std::cout << user->getName() << " tried to apply " << getEffectName() << " on " << target->getName() << "...\n";
			if (!critical) {
				std::cout << "and failed!\n\n";
			}
		}
		if (critical) {
			target->applyStatus(static_cast<Character::status>(effect));
		}
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
