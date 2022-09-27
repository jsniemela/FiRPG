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
	int target;
	std::vector<Character*> enemies;
	std::vector<Character*> friends;
	//std::vector<std::string> actions; // vector of abilities that the character has available. it should be able to change based on several factors.
	bool guarding;
	bool controlled;

	void chooseAction();
	void physicalAttack();
	void guard();

public:
	enum status { normal, poison, KO, slow, haste, petrify, protect, shell } condition;
	Character(std::string name, int hp, int atk, int def, int matk, int mdef, int crit, int spd, bool ctrl);// std::string name, int hp, int atk, int def, int matk, int mdef, int crit);

	void initializeStats(int hp, int atk, int def, int matk, int mdef, int crit, int spd);
	void dealDamage();
	void levelUp();
	void showStats();
	void takeDamage(float baseDamage, bool ignoreDefence);
	void die();
	void takeTurn();
	void applyStatus(status);
	void setTarget(int newTarget);
	void setEnemyList(std::vector<Character*> enms);
	void setPlayerList(std::vector<Character*> plrs);

	std::string getName();
	int getMaxHealth();
	int getCurrentHealth();
	int getAttack();
	int getMagicAttack();
	int getMagicDefence();
	int getCritRate();
	int getSpeed();
	enum status getStatus();
	int getTarget();
	bool getGuarding();
};