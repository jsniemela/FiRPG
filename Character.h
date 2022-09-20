#pragma once
#include "Randomizer.h"
#include "Weapon.h"
//#include "Battle.h"
#include <iostream>
#include <vector>

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
	int statusTimer;
	Character* target;
	static std::vector<Character> *enemies;
	static std::vector<Character> *friends;
public:
	enum status { normal, poison, KO, slow, haste, petrify, protect, shell } condition;
	Character(std::string name, int hp, int atk, int def, int matk, int mdef, int crit, int spd);// std::string name, int hp, int atk, int def, int matk, int mdef, int crit);

	void initializeStats(int hp, int atk, int def, int matk, int mdef, int crit, int spd);
	void dealDamage();
	void levelUp();
	void showStats();
	void takeDamage(float baseDamage, bool ignoreDefence);
	void die();
	void takeTurn();
	void applyStatus(status);
	void setTarget(Character* newTarget);

	std::string getName();
	int getMaxHealth();
	int getAttack();
	int getMagicAttack();
	int getMagicDefence();
	int getCritRate();
	int getSpeed();
	enum status getStatus();
};