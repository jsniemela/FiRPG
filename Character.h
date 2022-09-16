#pragma once
#include "Randomizer.h"
//#include "Battle.h"
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
	int speed;
	
public:
	enum status { normal, poison, KO, slow, haste, petrify, protect, shell } condition;
	Character(std::string name, int hp, int atk, int def, int matk, int mdef, int crit, int spd);// std::string name, int hp, int atk, int def, int matk, int mdef, int crit);

	void initializeStats(int hp, int atk, int def, int matk, int mdef, int crit, int spd);
	void dealDamage();
	void levelUp();
	void showStats();
	void dealDamage(Character &target);
	void takeDamage(float baseDamage, bool ignoreDefence);
	void die();
	void takeTurn();

	std::string getName();
	int getMaxHealth();
	int getAttack();
	int getMagicAttack();
	int getMagicDefence();
	int getCritRate();
	int getSpeed();
	enum status getStatus();
};