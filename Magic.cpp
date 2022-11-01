#include "Magic.h"
#include "Character.h"
/*
Magic::Magic() 
{

}
*/
Magic::Magic(std::string newName, int dmg, int sp, damageType dmgType, Element elem, bool req)
	:baseDamage{ dmg }, element {elem}, spCost {sp}
{
	name = newName;
	type = dmgType;
	requiresTarget = req;
	//requiresTarget = tgtAll;
}

int Magic::getSPcost()
{
	return spCost;
}

void Magic::useAction(Character* user, Character* target)
{
	int damage = user->getMagicAttack() + baseDamage;
	std::cout << user->getName() << " used " << name << "!\n";
	user->loseSP(spCost);
	if (element == healing)
	{
		target->recover(damage);
	} 
	else
	{
		target->takeDamage(damage, Character::magic, user, static_cast<Character::Element>(element));
	}
	if (element == ice)
	{
		target->applyStatus(Character::frozen);
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
		if (element == ice)
		{
			t->applyStatus(Character::frozen);
		}
	}

}