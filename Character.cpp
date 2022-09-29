#include "Character.h"
#include "Action.h"

Character::Character(std::string newName, int hp, int atk, int def, int matk, int mdef, int crit, int spd, bool ctrl) 
	: name{newName}, maxHealth{ hp },attack{atk}, defence{def}, magicAttack{matk}, magicDefence{mdef}, critRate{crit}, speed{spd} , controlled{ctrl}
{
	level = 1;
	currentHealth = maxHealth;
	condition = normal;
	statusTimer = 0;
	target = 0;
	guarding = false;
	initializeActions();
}

int Character::getMaxHealth()
{
	return maxHealth;
}
int Character::getCurrentHealth()
{
	return currentHealth;
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

/*
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
*/
void Character::initializeActions()
{
	actions.push_back(new Skill("Attack"));
	actions.push_back(new Skill("Block"));
	actions.push_back(new Skill("Skip turn")); 
	//std::cout << actions[0]->getName();
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

void Character::removeDeadTargets()
{
	enemies.erase( //removes dead targets
		std::remove_if(
			enemies.begin(),
			enemies.end(),
			[](Character* const& e) { return e->getStatus() == KO; }
		),
		enemies.end()
	);
}

void Character::chooseAction()
{
	if (controlled)
	{
		int action = 0;
		while (action < 1 || action > actions.size()) 
		{
			int i = 1;
			for (auto act : actions)
			{
				std::cout << "(" << i << ")";
				std::cout << act->getName() << std::endl;
				i++;
			}
			std::cout << "Choose action:";
			std::cin >> action;
			std::cout << std::endl;
		}
		int i = 1; // for target selection name print loop. 
		switch (action)
		{
			case 1:
				target = 0;
				for (auto en : enemies) 
				{
					std::cout << "(" << i << "): ";
					i++;
					std::cout << en->getName() << " - health: " << en->getCurrentHealth() << "\n";
				}
				
				while (target < 1 || target > enemies.size())
				{
					std::cout << "Choose target:";
					std::cin >> target;
					std::cout << std::endl;
				}
				target--; 
				physicalAttack();
				break;
			case 2:
				guard();
				break;
		}
	}
	else {
		int action = randomizeInt(0, 4); //80% change to attack, 20% change to block
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
		removeDeadTargets();
		std::cout << name << "'s turn.\n";
		target = randomizeInt(0, enemies.size() -1);
		if (enemies.size() > 0) {
			chooseAction();
			removeDeadTargets(); //remove again in case target(s) died.
		}
		else
		{
			std::cout << "No target available.\n";
		}
		if (condition != KO && enemies.size() > 0) {
			if (condition == poisoned) {
				float poisonDamage = static_cast<float>(maxHealth) / 10;
				std::cout << this->name << " is poisoned.\n";
				takeDamage(poisonDamage, poison);
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
		if (effect == poisoned)
		{
			std::cout << name << " is now poisoned.\n";
		}
	}
	else if (guarding)
	{
		std::cout << name << " avoided status by guarding. \n"; 
	}
}

void Character::dealDamage(Character* target)
{
	bool critical;
	critical = critRate >= randomizeInt(1, 100);

	float critBonus = 2.0f;
	std::cout << name << " attacks " << target->getName() << "!\n";
	if (critical) 
	{
		std::cout << "Critical Hit!\n";
		target->applyStatus(poisoned); //apply poison on critical hit (for testing purposes)
		target->takeDamage(static_cast<float>(attack) * critBonus, physical);
	}
	else
	{
		target->takeDamage(static_cast<float>(attack), physical);
	}
}

void Character::guard() {
	guarding = true;
	std::cout << name << " is guarding.\n\n";
}

void Character::physicalAttack() { // this will be more relevant once magic attacks are added
	dealDamage(enemies[target]);
}

void Character::takeDamage(float baseDamage, damageType dmgType) //add damage type here and maybe replace ignoreDefence if the type is always going to imply defence type anyway
{
	int damage; 
	// base damage is attack (+ possible crit), damage is base damage - defence
	if (dmgType == poison) {
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

