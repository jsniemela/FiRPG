#include "Character.h"

Character::Character(std::string newName, int hp, int atk, int def, int matk, int mdef, int crit, int spd, bool ctrl) 
	: name{newName}, maxHealth{ hp },attack{atk}, defence{def}, magicAttack{matk}, magicDefence{mdef}, critRate{crit}, speed{spd} , controlled{ctrl}
{
	level = 1;
	currentHealth = maxHealth;
	condition = normal;
	statusTimer = 0;
	target = 0;
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
int Character::getSpeed()
{
	return speed;
}
enum Character::status Character::getStatus() {
	return condition;
};
int Character::getTarget()
{
	return target;
}
std::string Character::getName()
{
	return name;
}

bool Character::getGuarding()
{
	return guarding;
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
	//actions = { "attack", "guard" };
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
	std::cout << "Health: " << currentHealth << "/" << maxHealth << "\n";
	/*
	std::cout << "Level: " << level << "\n";
	//std::cout << "Status: " << condition << "\n"; // prints number of the status affliction
	std::cout << "Attack: " << attack << "\n";
	std::cout << "Defence: " << defence << "\n";
	std::cout << "Magic Attack: " << magicAttack << "\n";
	std::cout << "Magic Defence: " << magicDefence << "\n";
	std::cout << "Crit Rate: " << critRate << "\n";
	*/
	std::cout << std::endl;
}

void Character::chooseAction()
{
	if (controlled)
	{
		int action = 0;
		while (action < 1 || action > 2) //change this later to use the number of available actions as max value
		{
			std::cout << "Choose action. (1) Attack (2) Guard: ";
			std::cin >> action;
			std::cout << "\n";
		}
		switch (action)
		{
			case 1:
				physicalAttack();
			case 2:
				guard();
		}
	}
	else {
		int action = randomizeInt(0, 4); //80% change to attack, 40% change to block
		if (action <= 3)
		{
			physicalAttack();
		}
		else
		{
			guard();
		}
	}
}

void Character::takeTurn()
{
	if (condition != KO)
	{
		//Checking targets might be unnecessary if the action doesn't require a target, but this also removes dead enemies so it might still be useful
		std::cout << name << "'s turn.\n";
		target = randomizeInt(1, static_cast<int>(enemies.size())) - 1;
		while (enemies[target]->getStatus() == KO && static_cast<int>(enemies.size()) > 0)
		{
			// delete from enemy list if dead and re-randomize
			enemies.erase(enemies.begin() + target);
			target = randomizeInt(1, static_cast<int>(enemies.size())) - 1; 
		}
		if (enemies[target]->getStatus() != KO)
		{
			chooseAction();
			if (enemies[target]->getStatus() == KO)
			{
				enemies.erase(enemies.begin() + target);
			}
		}
		else
		{
			std::cout << "No target available.\n";
		}
		if (condition != KO && static_cast<int>(enemies.size()) > 0) {
			if (condition == poison) {
				float poisonDamage = static_cast<float>(maxHealth) / 10;
				std::cout << this->name << " is poisoned.\n";
				takeDamage(poisonDamage, true);
			}

			if (statusTimer > 0) {
				statusTimer--; //decrement status effect timer by one each turn.
			}

			if (statusTimer == 0 && condition != normal && condition != KO)
			{
				std::cout << name << "'s status is back to normal.\n\n";
				condition = normal;
			}
		}
	}
	else
	{
		std::cout << name << " is dead. Can't act.\n";
	}
	
}

void Character::setEnemyList(std::vector<Character*> enms)
{
	enemies = enms;
}

void Character::setPlayerList(std::vector<Character*> plrs)
{
	friends = plrs;
}

void Character::setTarget(int newTarget)
{
	target = newTarget;
}

void Character::applyStatus(status effect) 
{
	if (statusTimer == 0 && !guarding) //guard block statuses
	{
		condition = effect;
		statusTimer = 3; //apply status for 3 turns 
		if (effect == poison)
		{
			std::cout << name << " is now poisoned.\n";
		}
	}
	else if (guarding)
	{
		std::cout << name << " avoided status by guarding. \n"; 
	}
}

void Character::dealDamage()
{
	bool critical;
	critical = critRate >= randomizeInt(1, 100);

	float critBonus = 2.0f;
	std::cout << name << " attacks " << enemies[target]->getName() << "!\n";
	if (critical) 
	{
		std::cout << "Critical Hit!\n";
		enemies[target]->applyStatus(poison); //apply poison on critical hit (for testing purposes)
		enemies[target]->takeDamage(static_cast<float>(attack) * critBonus, false);
	}
	else
	{
		enemies[target]->takeDamage(static_cast<float>(attack), false);
	}
}

void Character::guard() {
	guarding = true;
	std::cout << name << " is guarding.\n\n";
}

void Character::physicalAttack() { // this will be more relevant once magic attacks are added
	dealDamage();
}

void Character::takeDamage(float baseDamage, bool ignoreDefence) //add damage type here and maybe replace ignoreDefence if the type is always going to imply defence type anyway
{
	int damage; 
	// base damage is attack (+ possible crit), damage is base damage - defence
	if (ignoreDefence == true) {
		damage = static_cast<int>(baseDamage);
	}
	else
	{
		damage = static_cast<int>(baseDamage - defence);
	}
	if (damage < 0)
	{
		damage = 0;
	}
	if (guarding)
	{
		damage /= 2; // this applies to poison damage too. consider if it's desirable or not.
	}
	currentHealth -= damage;
	std::cout << name << " took " << damage << " damage.\n\n";
	//std::cout << "Current health: " << currentHealth << "\n";
	if (currentHealth < 0) {
		currentHealth = 0;
	}
	guarding = false;
	showStats();
	if (currentHealth == 0) {
		die();
	}
}

void Character::die()
{
	condition = KO;
	statusTimer = 0;
	std::cout << name << " died.\n\n";
}

