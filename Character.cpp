#include "Character.h"

Character::Character(std::string newName, int hp, int atk, int def, int matk, int mdef, int crit) 
	: name{newName}, maxHealth{ hp },attack{atk}, defence{def}, magicAttack{matk}, magicDefence{mdef}, critRate{crit}
{
	level = 1;
	currentHealth = maxHealth;
	condition = normal;
}

int Character::getMaxHealth()
{
	return maxHealth;
}
int Character::getAttack()
{
	return attack;
}
int Character::getMagicAttack()
{
	return magicAttack;
}
int Character::getMagicDefence()
{
	return magicDefence;
}
int Character::getCritRate()
{
	return critRate;
}
std::string Character::getName()
{
	return name;
}

void Character::initializeStats(int hp, int atk, int def, int matk, int mdef, int crit)
{
	level = 1;
	name = "newname";
	status condition;
	condition = normal;
	maxHealth = hp;
	currentHealth = maxHealth;
	attack = atk;
	defence = def;
	magicAttack = matk;
	magicDefence = mdef;
	critRate = crit;
}

void Character::levelUp() 
{
	//std::cout << "\n";
	level += 1;	
	maxHealth += randomizeInt(2, 10);
	currentHealth = maxHealth;
	attack += randomizeInt(1, 3);
	defence += randomizeInt(1, 3);
	magicAttack += randomizeInt(1, 3);
	magicDefence += randomizeInt(1, 3);
	
	std::cout << name << " leveled up!" << "\n\n";
}

void Character::showStats()
{
	std::cout << "Name: " << name << "\n";
	std::cout << "Level: " << level << "\n";
	//std::cout << "Status: " << condition << "\n"; // prints number of the status affliction
	std::cout << "Health: " << currentHealth << "/" << maxHealth << "\n";
	std::cout << "Attack: " << attack << "\n";
	std::cout << "Defence: " << defence << "\n";
	std::cout << "Magic Attack: " << magicAttack << "\n";
	std::cout << "Magic Defence: " << magicDefence << "\n";
	std::cout << "Crit Rate: " << critRate << "\n\n";
}

void Character::dealDamage(Character &target) 
{
	bool critical;
	critical = critRate >= randomizeInt(1, 100);

	float critBonus = 2.0f;
	std::cout << name << " attacks " << target.getName() << "!\n";
	if (critical) 
	{
		std::cout << "Critical Hit!\n";
		target.takeDamage(static_cast<float>(attack) * critBonus);
	}
	else
	{
		target.takeDamage(static_cast<float>(attack));
	}
}

void Character::takeDamage(float baseDamage) 
{
	// base damage is attack (+ possible crit), damage is base damage - defence
	float damage = baseDamage - defence;
	if (damage < 0)
	{
		damage = 0;
	}
	currentHealth -= static_cast<int>(damage);
	std::cout << name << " took " << damage << " damage.\n\n";
	//std::cout << "Current health: " << currentHealth << "\n";
	if (currentHealth < 0) {
		currentHealth = 0;
	}
	if (currentHealth == 0) {
		die();
	}
}

void Character::die()
{
	std::cout << name << " died.\n";
}

int main() 
{
	Character hero{ "Hero", 100, 60, 3, 7, 2, 10 };
	Character villain{ "Villain", 100, 10, 3, 7, 2, 10 };
	hero.levelUp();
	villain.levelUp();
	hero.showStats();
	std::cout << "\n";
	villain.showStats();
	std::cout << "\n";
	hero.dealDamage(villain);
	villain.showStats();
	//villain.levelUp();
	//villain.showStats();
	return 0;
}
