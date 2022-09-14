#include "Character.h"

Character::Character(std::string newName, int hp, int atk, int def, int matk, int mdef, int crit, int spd) 
	: name{newName}, maxHealth{ hp },attack{atk}, defence{def}, magicAttack{matk}, magicDefence{mdef}, critRate{crit}, speed{spd}
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

void Character::initializeStats(int hp, int atk, int def, int matk, int mdef, int crit, int spd)
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
	speed = spd;
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

void Character::takeTurn()
{
	std::cout << this->name << "'s turn.\n";
	if (condition == poison) {
		// Change this to apply poison damage after attacking?
		float poisonDamage = static_cast<float>(maxHealth) / 10;
		std::cout << this->name << " is poisoned.\n";
		takeDamage(poisonDamage, true);
	}
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
		target.takeDamage(static_cast<float>(attack) * critBonus, false);
	}
	else
	{
		target.takeDamage(static_cast<float>(attack), false);
	}
}

void Character::takeDamage(float baseDamage, bool ignoreDefence) 
{
	float damage; 
	// base damage is attack (+ possible crit), damage is base damage - defence
	if (ignoreDefence == true) {
		damage = baseDamage;
	}
	else
	{
		damage = baseDamage - defence;
	}
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

