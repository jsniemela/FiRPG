#include "Character.h"
#include "Skill.h"

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
}

std::string Character::getStatusName() {
	std::string status = "";
	switch (condition) {
	case 0:
		return "healthy";
	case 1:
		return "poisoned";
	case 2:
		return "KO";
	case 3:
		return "sad";
	default:
		return "healthy";
	}
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

void Character::initializeActions()
{
	actions.push_back(new Skill("Attack", 10, Skill::physical));
	actions.push_back(new Skill("Block", false));
	actions.push_back(new Skill("Poison attack", 5, Skill::physical, Skill::poisoned));
	actions.push_back(new Skill("Insult", 0, Skill::physical, Skill::sadness));
	actions.push_back(new Skill("Kill", 0, Skill::statusOnly, Skill::KO));
	//actions.push_back(new Skill("Skip turn", 0, Skill::physical)); 
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
	std::cout << name << " - HP: " << currentHealth << "/" << maxHealth << " HP";
	if (condition != normal) {
		std::cout << ", status: " << getStatusName();
	}
	
	/*
	std::cout << "Level: " << level << "\n";
	//std::cout << "Status: " << condition << "\n"; // prints number of the status affliction
	std::cout << "Attack: " << attack << "\n";
	std::cout << "Defence: " << defence << "\n";
	std::cout << "Magic Attack: " << magicAttack << "\n";
	std::cout << "Magic Defence: " << magicDefence << "\n";
	std::cout << "Crit Rate: " << critRate << "\n";
	*/
	std::cout << "\n\n";
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

void Character::targetSelection()
{
	int i = 1;
	target = 0;
	for (auto en : enemies)
	{
		std::cout << "(" << i << "): ";
		i++;
		std::cout << en->getName() << " - " << en->getCurrentHealth() << "/" << en->getMaxHealth() << " HP, status: " << en->getStatusName() << "\n";
	}

	while (target < 1 || target > enemies.size())
	{
		std::cout << "Choose target:";
		std::cin >> target;
		std::cout << std::endl;
	}
	target--;
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
		action--;
		if (static_cast<Skill*>(actions[action])->getRequiresTarget()) {
			targetSelection();
			static_cast<Skill*>(actions[action])->useAction(this, enemies[target], attack, critRate);
		}
		else
		{
			static_cast<Skill*>(actions[action])->useAction(this);
		}
	}
	else {
		int action = randomizeInt(0, actions.size() -1); 
		if (static_cast<Skill*>(actions[action])->getRequiresTarget()) {
			target = randomizeInt(0, enemies.size() - 1);
			static_cast<Skill*>(actions[action])->useAction(this, enemies[target], attack, critRate);
		}
		else
		{
			static_cast<Skill*>(actions[action])->useAction(this);
		}
	}
}

void Character::takeTurn()
{
	guarding = false;
	bool skipTurn = false;
	if (condition != KO)
	{
		if (condition == sadness) {
			if (int x = randomizeInt(1, 10) > 4) //chance to skip turn.
			{
				skipTurn = true;
				std::cout << name << " skips a turn while wallowing in sadness.\n\n";
			}
		}
		removeDeadTargets();
		if (!skipTurn)
		{
			std::cout << name << "'s turn.\n";
			target = randomizeInt(0, enemies.size() - 1);
			if (enemies.size() > 0) {
				chooseAction();
				removeDeadTargets(); //remove again in case target(s) died.
			}
			else
			{
				std::cout << "No target available.\n";
			}
		}
		if (condition != KO && enemies.size() > 0) {
			if (condition == poisoned) {
				float poisonDamage = static_cast<float>(maxHealth) / 10;
				std::cout << this->name << " is poisoned.\n";
				takeDamage(poisonDamage, ignoreDef);
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

void Character::setHealth(int hp) {
	currentHealth = hp;
}

void Character::applyStatus(status effect) 
{
	if (guarding)
	{
		std::cout << name << " avoided status by guarding. \n\n";
	}
	else
	{
		if (effect == KO) {
			die();
		}
		else {
			condition = effect;
			statusTimer = 3; //apply status for 3 turns 
			std::cout << name << "'s status is now " << getStatusName() << ".\n\n";
		}
	}
}

void Character::guard() {
	guarding = true;
	std::cout << name << " is guarding.\n\n";
}

void Character::takeDamage(float baseDamage, damageType dmgType) //add damage type here and maybe replace ignoreDefence if the type is always going to imply defence type anyway
{
	int damage; 
	// base damage is attack (+ possible crit), damage is base damage - defence
	if (dmgType == Skill::poisoned) {
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
	if (guarding && dmgType != ignoreDef)
	{
		damage /= 2; 
	}
	currentHealth -= damage;
	std::cout << name << " took " << damage << " damage.\n\n";
	//std::cout << "Current health: " << currentHealth << "\n";
	if (currentHealth < 0) {
		currentHealth = 0;
	}
	showStats();
	if (currentHealth == 0) {
		die();
	}
}

void Character::die()
{
	condition = KO;
	currentHealth = 0;
	statusTimer = 0;
	std::cout << name << " died.\n\n";
}

