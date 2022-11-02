#pragma once
#include "Randomizer.h"
#include "Weapon.h"
//#include "Battle.h"
#include <iostream>
#include <vector>

class Skill;
class Magic;
class Action;

class Character 
{
private:
	int level;
	std::string name;
	int currentHealth;
	int maxHealth;
	int currentSP;
	int maxSP;
	int attack;
	int defence;
	int magicAttack;
	int magicDefence;
	int critRate;
	int speed;
	int statusTimer; // status ends when timer goes to zero.
	int target;
	int exp; // total gained exp
	int expDrop; // how much a character gives exp to enemies after battle
	std::vector<Character*> enemies;
	std::vector<Character*> friends;
	std::vector<Action*> actions;
	bool guarding;
	bool counter;
	bool controlled;
	Weapon* equippedWeapon;

	void chooseAction();
	void initializeActions();
	void removeDeadTargets();
	void targetSelection(std::vector<Character*> targets);
	void die();
	void callAction(Action* act);
	bool checkLevelUp();
	int requiredExp();
	void learnSkill(Skill* skill);

public:
	enum status { normal, poisoned, KO, sadness, sleep, frozen, burning } condition;
	enum damageType { physical, ignoreDef, magic } dmgType;
	enum Element { fire, ice, healing, none } element;
	enum Weakness { wFire, wIce, wHealing, wNone } weakness;
	Character(std::string name, int hp, int sp, int atk, int def, int matk, int mdef, int crit, int spd, bool ctrl, Weakness wkn = Weakness::wNone);

	Skill* getSkill();
	Magic* getMagic();
	Action* getAction();

	void dealDamage(Character* target);
	void gainExp(int expGain);
	void levelUp();
	void showStats();
	void takeDamage(int baseDamage, damageType dmgType, Character* damager, Element elem = none);
	void takeTurn();
	void applyStatus(status effect);
	void guard();
	void recover(int healAmount);
	void recoverSP(int healAmount);
	void loseSP(int spLoss);
	void recoverStatus();
	void EquipWeapon(Weapon* wpn);
	void unEquipWeapon();

	std::string getName();
	int getMaxHealth();
	int getCurrentHealth();
	int getCurrentSP();
	int getMaxSP();
	int getAttack();
	int getMagicAttack();
	int getMagicDefence();
	int getCritRate();
	int getSpeed();
	status getStatus();
	std::string getStatusName();
	int getTarget();
	bool getGuarding();
	int getExpDrop();

	void setHealth(int hp);
	void setEnemyList(std::vector<Character*> enms);
	void setPlayerList(std::vector<Character*> plrs);

protected:
	Skill* s;
	Action* a;
};