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
	:baseDamage{atk}
{
	name = newName;
	requiresTarget = true;
	type = dmgType;
}

Skill::Skill(std::string newName, int atk, damageType dmgType, status eff)
	:baseDamage{ atk }, effect{eff}
{
	name = newName;
	type = dmgType;
	requiresTarget = true;
}

std::string Skill::getEffectName() 
{
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

void Skill::useAction(Character* user, Character* target)
{
	bool critical;
	float critrate = static_cast<float>(user->getCritRate());
	if (type == statusOnly) 
	{
		critrate *= 1.4f; // higher chance for status if skill doesn't apply damage.
	}
	if (target->getStatus() == static_cast<Character::status>(sadness)) 
	{
		critrate *= 2.0f; // higher crit rate if target is sad
	}
	if (critrate > 100)
	{
		critrate = 100;
	}
	critrate = static_cast<int>(critrate);
	std::cout << critrate << "/100 chance for critical attack.\n";
	critical = critrate >= randomizeInt(1, 100); //true if critical
	if (type != statusOnly) 
	{
		std::cout << user->getName() << " uses " << name << " on " << target->getName() << "!\n";
		float damage = calculateDamage(user->getAttack(), critical);
		target->takeDamage(damage, Character::physical);
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
		if (critical) 
		{
			target->applyStatus(static_cast<Character::status>(effect));
		}
	}
}

float Skill::calculateDamage(float damage, bool crit) 
{
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
