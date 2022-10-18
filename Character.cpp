#include "Character.h"
#include "Skill.h"
#include "Magic.h"

Character::Character(std::string newName, int hp, int sp, int atk, int def, int matk, int mdef, int crit, int spd, bool ctrl) 
	: name{newName}, maxHealth{ hp }, maxSP{sp}, attack{atk}, defence{def}, magicAttack{matk}, magicDefence{mdef}, critRate{crit}, speed{spd} , controlled{ctrl}
{
	level = 1;
	currentHealth = maxHealth;
	currentSP = maxSP;
	condition = normal;
	statusTimer = 0;
	target = 0;
	guarding = false;
	counter = false;
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
enum Character::status Character::getStatus() 
{
	return condition;
}

std::string Character::getStatusName() 
{
	std::string status = "";
	switch (condition) 
	{
	case 0:
		return "healthy";
	case 1:
		return "poisoned";
	case 2:
		return "KO";
	case 3:
		return "sad";
	case 4:
		return "sleeping";
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
	actions.push_back(new Skill("Attack", 0, 0, Action::basic));
	actions.push_back(new Skill("Block", Action::basic, false));
	actions.push_back(new Skill("Poison attack", 5, 5, Action::physical, Skill::poisoned, 0)); // 0% to apply status, uses critrate instead
	actions.push_back(new Skill("Spin attack", 0, 5, Action::physical, false));
	actions.push_back(new Skill("Explode", &currentHealth, &currentHealth, 2, 0, Action::physical, false)); // use all health to deal 50% (minus opponents defense) of it to all enemies
	actions.push_back(new Skill("Insult", 0, 0, Action::statusOnly, Skill::sadness, 50)); // 50% to apply sadness
	actions.push_back(new Skill("Kill", 0, 0, Action::statusOnly, Skill::KO, 15));
	actions.push_back(new Skill("Sleep", 0, 0, Action::statusOnly, Skill::sleep, 50));
	actions.push_back(new Magic("Fire", 30, 5, Action::magic, Magic::fire, true));
	actions.push_back(new Magic("Blizzard", 10, 7, Action::magic, Magic::ice, false)); 
	actions.push_back(new Magic("Cure", 25, 6, Action::magic, Magic::healing, true));
	actions.push_back(new Magic("Cure All", 10, 10, Action::magic, Magic::healing, false));
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
	std::cout << name << " - HP: " << currentHealth << "/" << maxHealth;
	std::cout << ", SP: " << currentSP << "/" << maxSP;
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

void Character::targetSelection(std::vector<Character*> targets)
{

	if (controlled)
	{
		int i = 1;
		target = -1;
		for (auto t : targets)
		{
			std::cout << "(" << i << "): ";
			i++;
			std::cout << t->getName() << " - " << t->getCurrentHealth() << "/" << t->getMaxHealth() << " HP, status: " << t->getStatusName() << "\n";
		}
		std::cout << "(0): [Go back]" << std::endl;
		while (target < 0 || target > targets.size())
		{
			std::cout << "Choose target:";
			std::cin >> target;
			std::cout << std::endl;
		}
		target--;
	}
	else
	{
		target = randomizeInt(0, targets.size() - 1);
	}
}

void Character::loseSP(int spLoss)
{
	currentSP -= spLoss;
	if (currentSP < 0)
	{
		currentSP = 0;
	}
	std::cout << name << " now has " << currentSP << "/" << maxSP << " SP. \n";
}

void Character::chooseAction()
{
	int command = 0;
	int action = -1;
	
	if (controlled)
	{
		while (command < 1 || command > 4)
		{
			std::cout << "(1)Attack\n";
			std::cout << "(2)Magic\n";
			std::cout << "(3)Skill\n";
			std::cout << "(4)Guard\n";
			std::cout << "Choose command: ";
			std::cin >> command;
		}
		
		if (command == 1) // attack
		{
			callAction(actions[0]);
		}

		else if (command == 2) // magic
		{
			std::vector<Magic*>magics;
			int i = 1;
			for (auto act : actions)
			{
				if (act->type == Action::magic)
				{
					std::cout << "(" << i << ") ";
					std::cout << act->getName();
					std::cout << " [" << static_cast<Magic*>(act)->getSPcost() << " SP]";
					std::cout << std::endl;
					magics.push_back(static_cast<Magic*>(act));
					i++;
				}
			}
			std::cout << "(0) [Go back]" << std::endl;
			std::cout << "Choose magic: ";
			std::cin >> action;
			std::cout << std::endl;
			if (action > 0 && action <= magics.size() && magics[action-1]->getSPcost() > currentSP)
			{
				std::cout << "Not enough SP!\n\n";
				action = 0;
			}
			if (action < 1 || action > magics.size())
			{
				chooseAction();
				return;
			}
			callAction(magics[action - 1]);
		}
		else if (command == 3) // skill
		{
			std::vector<Skill*>skills;
			int i = 1;
			for (auto act : actions)
			{
				if (act->type == Action::physical || act->type == Action::statusOnly)
				{
					std::cout << "(" << i << ") ";
					std::cout << act->getName();
					if (static_cast<Skill*>(act)->getHPcost() > 0)
					{
						std::cout << " [" << static_cast<Skill*>(act)->getHPcost() << " HP]";
					}
					std::cout << std::endl;
					skills.push_back(static_cast<Skill*>(act));
					i++;
				}
			}
			std::cout << "(0) [Go back]" << std::endl;
			std::cout << "Choose skill: ";
			std::cin >> action;
			std::cout << std::endl;
			if (action < 1 || action > skills.size())
			{
				chooseAction();
				return;
			}
			callAction(skills[action - 1]);
		}
		else if (command == 4) // guard
		{
			callAction(actions[1]);
		}
		action--;
	}
	else
	{
		action = randomizeInt(0, actions.size() - 1);
		if (actions[action]->type == Action::magic && static_cast<Magic*>(actions[action])->getSPcost() > currentSP)
		{
			chooseAction(); //restart action randomization if not enough SP.
			return;
		}
		callAction(actions[action]);
	}
}

void Character::callAction(Action* act)
{
	if (act->getRequiresTarget())
	{
		if (act->type == Action::magic && static_cast<Magic*>(act)->element == Action::healing)
		{
			targetSelection(friends);
			if (target == -1)
			{
				chooseAction();
				return;
			}
			if (friends[target]->getCurrentHealth() == friends[target]->getMaxHealth())
			{
				if (controlled)
				{
					std::cout << "Target health is already full.\n\n";
				}
				chooseAction();
				return;
			}
		}
		else 
		{
			targetSelection(enemies);
			if (target == -1)
			{
				chooseAction();
				return;
			}
		}
		if (act->type == Action::physical || act->type == Action::basic || act->type == Action::statusOnly)
		{
			//std::cout << "Action is physical\n";
			static_cast<Skill*>(act)->useAction(this, enemies[target]);
		}
		if (act->type == Action::magic)
		{
			//std::cout << "Action is magical\n";
			if (static_cast<Magic*>(act)->element == Action::healing)
			{
				static_cast<Magic*>(act)->useAction(this, friends[target]);
			}
			else
			{
				static_cast<Magic*>(act)->useAction(this, enemies[target]);
			}
		}
	}
	else
	{
		if (act->type == Action::physical || act->type == Action::basic)
		{
			//std::cout << "Action is physical\n";
			static_cast<Skill*>(act)->useAction(this, enemies);
		}
		if (act->type == Action::magic)
		{
			//std::cout << "Action is magical\n";
			if (static_cast<Magic*>(act)->element == Action::healing)
			{
				int i = friends.size();
				for (auto fr : friends)
				{
					if (fr->getCurrentHealth() == friends[target]->getMaxHealth())
					{
						i--;
					}
				}
				if (i == 0) {
					if (controlled)
					{
						std::cout << "All targets are already at full health.\n\n";
					}
					chooseAction();
					return;
				}
				else
				{
					static_cast<Magic*>(act)->useAction(this, friends);
				}
			}
			else
			{
				static_cast<Magic*>(act)->useAction(this, enemies);
			}
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
		if (condition == sleep) 
		{
			skipTurn = true;
			std::cout << name << " is sleeping.\n\n";
		}
		removeDeadTargets();
		if (!skipTurn)
		{
			std::cout << name << "'s turn.\n";
			showStats();
			target = randomizeInt(0, enemies.size() - 1);
			if (enemies.size() > 0) 
			{
				chooseAction();
				removeDeadTargets(); //remove again in case target(s) died.
			}
			else
			{
				std::cout << "No target available.\n";
			}
		}
		if (condition != KO && enemies.size() > 0) 
		{
			if (condition == poisoned) 
			{
				float poisonDamage = static_cast<float>(maxHealth) / 10;
				std::cout << this->name << " is poisoned.\n";
				takeDamage(poisonDamage, ignoreDef, this);
			}

			if (statusTimer > 0) 
			{
				statusTimer--; //decrement status effect timer by one each turn.
			}

			if (statusTimer == 0 && condition != normal && condition != KO)
			{
				if (condition == sleep)
				{
					std::cout << name << " woke up!\n\n";
				}
				else {
					std::cout << name << "'s status is back to normal.\n\n";
				}
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

void Character::setHealth(int hp) 
{
	currentHealth = hp;
}

void Character::applyStatus(status effect) 
{
	if (condition != KO)
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
			else
			{
				condition = effect;
				statusTimer = 3; //apply status for 3 turns 
				std::cout << name << " is now " << getStatusName() << ".\n\n";
			}
		}
	}
}

void Character::guard() 
{
	guarding = true;
	counter = true;
	std::cout << name << " is guarding.\n\n";
}

void Character::takeDamage(float baseDamage, damageType dmgType, Character* damager) //add damage type here and maybe replace ignoreDefence if the type is always going to imply defence type anyway
{
	int damage = baseDamage; 
	// base damage is attack (+ possible crit), damage is base damage - defence
	if (dmgType == physical)
	{
		damage -= defence;
	}
	else if (dmgType == magic)
	{
		damage -= magicDefence;
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
	std::cout << name << " took " << damage << " damage.\n";
	if (dmgType == physical && condition == sleep && randomizeInt(0, 1) == 1)
	{
		statusTimer = 0;
		condition = normal;
		std::cout << name << " woke up!\n\n";
	}
	std::cout << "\n";
	//std::cout << "Current health: " << currentHealth << "\n";
	if (currentHealth < 0) 
	{
		currentHealth = 0;
	}
	showStats();
	if (currentHealth == 0) 
	{
		die();
	}
	else if (counter && dmgType == physical)
	{
		std::cout << "Counter attack!\n";
		static_cast<Skill*>(actions[0])->useAction(this, damager);
		counter = false;
	}
}

void Character::recover(int healAmount)
{
	currentHealth += healAmount;
	if (currentHealth >= maxHealth)
	{
		currentHealth = maxHealth;
		std::cout << name << " recovered to full HP.\n\n";
	} 
	else
	{
		std::cout << name << " recovered " << healAmount << " HP.\n\n";
	}
	showStats();
}

void Character::die()
{
	condition = KO;
	currentHealth = 0;
	statusTimer = 0;
	std::cout << name << " died.\n\n";
}

