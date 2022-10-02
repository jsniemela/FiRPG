#pragma once
#include "Randomizer.h"
#include "Weapon.h"
//#include "Battle.h"
#include <iostream>
#include <vector>

class Skill;
class Action;

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
	std::vector<Action*> actions;
	bool guarding;
	bool controlled;

	void chooseAction();
	void initializeActions();
	void removeDeadTargets();
	void targetSelection();
	void die();

public:
	enum status { normal, poisoned, KO, sadness } condition;
	enum damageType { physical, poison, fire, ice } dmgType;
	Character(std::string name, int hp, int atk, int def, int matk, int mdef, int crit, int spd, bool ctrl);// std::string name, int hp, int atk, int def, int matk, int mdef, int crit);

	Skill* getSkill();
	Action* getAction();

	void dealDamage(Character* target);
	void levelUp();
	void showStats();
	void takeDamage(float baseDamage, damageType dmgType);
	void takeTurn();
	void applyStatus(status effect);
	void guard();

	std::string getName();
	int getMaxHealth();
	int getCurrentHealth();
	int getAttack();
	int getMagicAttack();
	int getMagicDefence();
	int getCritRate();
	int getSpeed();
	status getStatus();
	std::string getStatusName();
	int getTarget();
	bool getGuarding();

	void setHealth(int hp);
	void setEnemyList(std::vector<Character*> enms);
	void setPlayerList(std::vector<Character*> plrs);

protected:
	Skill* s;
	Action* a;
};