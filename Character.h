#pragma once
#include "Randomizer.h"
#include <iostream>

class Character 
{
private:
	int level;
	std::string name;
	int currentHealth;
	int maxHealth;
	int attack;
	int defence;
	int magicAttack;
	int magicDefence;
	int critRate;
public:
	Character(std::string name, int hp, int atk, int def, int matk, int mdef, int crit);// std::string name, int hp, int atk, int def, int matk, int mdef, int crit);

	void initializeStats(int hp, int atk, int def, int matk, int mdef, int crit);
	void dealDamage();
	void levelUp();
	void showStats();
	void dealDamage(Character &target);
	void takeDamage(float baseDamage);

	std::string getName();
	int getMaxHealth();
	int getAttack();
	int getMagicAttack();
	int getMagicDefence();
	int getCritRate();
};