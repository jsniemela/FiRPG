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
	else if (element == ice)
	{
		target->takeDamage(damage, Character::magic, user, Character::Element::ice);
		target->applyStatus(Character::frozen);
	}
	else if (element == fire)
	{
		target->takeDamage(damage, Character::magic, user, Character::Element::fire);
	}
	else
	{
		target->takeDamage(damage, Character::magic, user);
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
		else if (element == ice)
		{
			t->takeDamage(damage, Character::magic, user, Character::Element::ice);
			t->applyStatus(Character::frozen);
		}
		else if (element == fire)
		{
			t->takeDamage(damage, Character::magic, user, Character::Element::fire);
		}
		else
		{
			t->takeDamage(damage, Character::magic, user);
		}
	}

}