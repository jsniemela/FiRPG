#include "Magic.h"
#include "Character.h"

Magic::Magic(std::string newName, int dmg, int sp, DamageType dmgType, Element elem, bool req, Status eff)
	:baseDamage{ dmg }, element {elem}, spCost {sp}
{
	name = newName;
	type = dmgType;
	requiresTarget = req;
	effect = eff;
}

int Magic::getSPcost()
{
	return spCost;
}

void Magic::useAction(Character* user, Character* target)
{
	int damage = baseDamage;
	if (baseDamage != 0)
	{
		damage += user->getMagicAttack(); //only adds magic attack to damage to spells that are supposed to deal damage or heal.
	}
	std::cout << user->getName() << " used " << name << "!\n";
	user->loseSP(spCost);
	if (element == healing)
	{
		if (damage != 0)
		{
			target->recover(damage);
		}
		if (effect == normal)
		{
			target->recoverStatus();
		}
	} 
	else
	{
		target->takeDamage(damage, Character::magic, user, static_cast<Character::Element>(element));
	}
	if (effect != nothing)
	{
		target->applyStatus(static_cast<Character::Status>(effect));
	}
}

void Magic::useAction(Character* user, std::vector<Character*> targets)
{
	int damage = user->getMagicAttack() + baseDamage;
	std::cout << user->getName() << " used " << name << "!\n";
	user->loseSP(spCost);
	for (auto t : targets) 
	{
		if (element == healing)
		{
			if (t->condition != Character::KO)
			{
				t->recover(damage);
			}
			else
			{
				std::cout << t->getName() << " can't be healed while dead.\n";
			}
		}
		else 
		{
			t->takeDamage(damage, Character::magic, user, static_cast<Character::Element>(element));
		}
		if (effect != nothing)
		{
			t->applyStatus(static_cast<Character::Status>(effect));
		}
	}

}