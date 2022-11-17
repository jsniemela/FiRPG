#include "Character.h"
#include "Skill.h"
#include "Magic.h"
#include <cmath>

Character::Character(std::string newName, int hp, int sp, int atk, int def, int matk, int mdef, int crit, int spd, bool ctrl, Weakness wkn) 
	: name{newName}, maxHealth{ hp }, maxSP{sp}, attack{atk}, defence{def}, magicAttack{matk}, magicDefence{mdef}, critRate{crit}, speed{spd} , controlled{ctrl}, weakness{wkn}
{
	level = 1;
	currentHealth = maxHealth;
	currentSP = maxSP;
	condition = normal; // TODO: make it possible to have multiple conditions and "normal" should mean that there are no status effects
	//statusTimer = 0;
	target = 0;
	guarding = false;
	counter = false;
	expDrop = 50;
	equippedWeapon = new Weapon(Weapon::fists, 0, "Fists");
	skipTurn = false;
	defMultiplier = 1.0f;
	mDefMultiplier = 1.0f;
	initializeActions();
}

void Character::gainExp(int expGain)
{
	exp += expGain;
	std::cout << name << " gained " << expGain << " experience.\n\n";
	while (checkLevelUp())
	{
		std::cout << name << " needs " << requiredExp() << " for next level.\n";
		exp -= requiredExp();
		levelUp();
	}
}

bool Character::checkLevelUp()
{
	if (exp > requiredExp())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Character::requiredExp()
{
	int reqExp = static_cast<int>(std::round(100 * pow((1+0.2), level)));
	return reqExp;
}

int Character::getMaxHealth()
{
	return maxHealth;
}
int Character::getCurrentHealth()
{
	return currentHealth;
}
int Character::getCurrentSP()
{
	return currentSP;
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
enum Character::Effect Character::getStatus() 
{
	return condition;
}
int Character::getExpDrop()
{
	return expDrop;
}
/*
std::string Character::getStatusName() 
{
	switch (condition) 
	{
	case 0:
		return "nothing";
	case 1:
		return "healthy";
	case 2:
		return "KO";
	case 3:
		return "poisoned";
	case 4:
		return "sad";
	case 5:
		return "sleeping";
	case 6:
		return "frozen";
	case 7:
		return "burning";
	case 8:
		return "protected";
	case 9:
		return "shelled";
	default:
		return "healthy";
	}
};
*/
std::string Character::getWeaknessName()
{
	switch (weakness)
	{
	case Weakness::fire:
		return "Fire";
	case Weakness::ice:
		return "Ice";
	case Weakness::healing:
		return "Healing";
	case Weakness::none:
		return "None";
	default:
		return "None";
	}
};
int Character::getMaxSP()
{
	return maxSP;
}
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
	actions.push_back(new Skill("Insult", 0, 0, Action::statusOnly, Skill::sadness, 50)); // 50% to apply sadness
	actions.push_back(new Skill("Sleep", 0, 0, Action::statusOnly, Skill::sleep, 50));
	actions.push_back(new Skill("Kill", 0, 0, Action::statusOnly, Skill::KO, 15));
	actions.push_back(new Magic("Fire", 30, 5, Action::magic, Magic::fire, true, Action::burning));
	actions.push_back(new Magic("Fire Storm", 15, 10, Action::magic, Magic::fire, false, Action::burning));
	actions.push_back(new Magic("Freeze", 15, 5, Action::magic, Magic::ice, true, Action::frozen));
	actions.push_back(new Magic("Blizzard", 10, 10, Action::magic, Magic::ice, false, Action::frozen));
	actions.push_back(new Magic("Cure", 25, 6, Action::magic, Magic::healing, true));
	actions.push_back(new Magic("Protect", 0, 6, Action::magic, Magic::healing, true, Action::protect));
	actions.push_back(new Magic("Shell", 0, 6, Action::magic, Magic::healing, true, Action::shell));
	actions.push_back(new Magic("Cleanse", 0, 5, Action::magic, Magic::healing, true, Action::normal)); // cure status
	actions.push_back(new Magic("Revive", 0, 5, Action::magic, Magic::revival, true, Action::normal)); // cure KO
	actions.push_back(new Magic("Cure All", 10, 10, Action::magic, Magic::healing, false));
	actions.push_back(new Skill("Analyze", 0, 0, Action::analyze, true));
}

void Character::learnAction(Action* action, bool notify)
{
	actions.push_back(action);
	if (notify)
	{
		std::cout << name << " learned " << action->getName() << "!\n";
	}
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
	std::cout << name << " leveled up!" << "\n";
	
	if (level == 2)
	{
		actions.push_back(new Skill("Explode", &currentHealth, &currentHealth, 2, 0, Action::physical, false)); // use all health to deal 50% (minus opponents defense) of it to all enemies
	}
	
	std::cout << "\n";
}

void Character::showStats()
{
	std::cout << name << " - Level " << level << ", HP: " << currentHealth << " / " << maxHealth;
	std::cout << ", SP: " << currentSP << "/" << maxSP;
	if (statuses.size() > 0)
	{
		std::cout << ", statuses: ";
		for (auto s : statuses)
		{
			std::cout << s->name << " ";
		}
		//std::cout << "\n";
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
			std::cout << t->getName() << " - " << t->getCurrentHealth() << "/" << t->getMaxHealth() << " HP";
			if (t->statuses.size() > 0)
			{
				std::cout << ", status: ";
				for (auto st : t->statuses)
				{
					std::cout << st->name << " ";
				}
			}
			std::cout << "\n";
		}
		std::cout << "(0): [Go back]" << std::endl;
		while (target < 0 || target > targets.size())
		{
			std::cout << "Choose target:";
			std::cin >> target;
			if (std::cin.fail())
			{
				target = -1;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			std::cout << std::endl;
		}
		target--;
	}
	else
	{
		target = randomizeInt(0, static_cast<int>(targets.size()) - 1);
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
			if (std::cin.fail())
			{
				command = -1;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		
		if (command == 1) // attack
		{
			callAction(actions[0]);
		}

		else if (command == 2) // magic
		{
			std::vector<Magic*>magics;
			int i = 1;
			while (action < 0 || action > magics.size())
			{
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
				if (std::cin.fail())
				{
					action = -1;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				std::cout << std::endl;
				i = 1;
			}
			
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
			while (action < 0 || action > skills.size())
			{
				for (auto act : actions)
				{
					if (act->type == Action::physical || act->type == Action::statusOnly || act->type == Action::analyze)
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
				if (std::cin.fail())
				{
					action = -1;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				std::cout << std::endl;
				i = 1;
			}
			if (action < 1 || action > skills.size())
			{
				chooseAction();
				return;
			}
			callAction(skills[action - 1]);
		}
		else if (command == 4) // guard
		{
			/*
			if (condition == burning)
			{
				recoverStatus();
			}
			*/
			callAction(actions[1]);
		}
		action--;
	}
	else
	{
		action = randomizeInt(0, static_cast<int>(actions.size()) - 1);
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
		if (act->type == Action::magic && static_cast<Magic*>(act)->element == Magic::healing || static_cast<Magic*>(act)->element == Magic::revival)
		{
			targetSelection(friends);
			if (target == -1)
			{
				chooseAction();
				return;
			}
			if (friends[target]->getCurrentHealth() == friends[target]->getMaxHealth() && static_cast<Magic*>(act)->effect == Action::nothing)
			{
				if (controlled)
				{
					std::cout << "Target is already at full health.\n\n";
				}
				chooseAction();
				return;
			}
			//temporarily disabled
			/*
			if (static_cast<Magic*>(act)->element == Magic::healing && static_cast<Magic*>(act)->effect == Action::normal && friends[target]->getStatus() == normal)
			{
				if (controlled)
				{
					std::cout << "Target's condition is already normal.\n\n";
				}
				chooseAction();
				return;
			}
			*/
			if (static_cast<Magic*>(act)->element == Magic::revival && friends[target]->getStatus() != KO)
			{
				if (controlled)
				{
					std::cout << "Target is not KO'd.\n\n";
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
		if (act->type == Action::physical || act->type == Action::basic || act->type == Action::statusOnly || act->type == Action::analyze)
		{
			// action is a skill
			static_cast<Skill*>(act)->useAction(this, enemies[target]);
		}
		if (act->type == Action::magic)
		{
			// action is magic
			if (static_cast<Magic*>(act)->element == Magic::healing || static_cast<Magic*>(act)->element == Magic::revival)
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
			if (static_cast<Magic*>(act)->element == Magic::healing || static_cast<Magic*>(act)->element == Magic::revival)
			{
				int i = static_cast<int>(friends.size());
				for (auto fr : friends)
				{
					if (fr->getCurrentHealth() == fr->getMaxHealth())
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
	/*
	if (condition == burning)
	{
		std::cout << name << " is burning.\n";
		takeDamage(static_cast<int>(maxHealth * 0.2), ignoreDef, this);
	}
	*/
}

void Character::takeTurn()
{
	guarding = false;
	skipTurn = false;
	if (condition != KO)
	{
		statusTick(0);
		/*
		if (condition == sadness) {
			if (int x = randomizeInt(1, 10) > 4) //chance to skip turn.
			{
				skipTurn = true;
				std::cout << name << " skips a turn while wallowing in sadness.\n\n";
			}
		}
		else if (condition == sleep) 
		{
			skipTurn = true;
			std::cout << name << " is sleeping.\n\n";
		}
		else if (condition == frozen)
		{
			skipTurn = true;
			std::cout << name << " skips a turn while defrosting.\n\n";
		}
		*/
		removeDeadTargets();
		if (!skipTurn)
		{
			std::cout << "\n" << name << "'s turn.\n";
			showStats();
			target = randomizeInt(0, static_cast<int>(enemies.size()) - 1);
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
			statusTick(1);
			/*
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
			*/
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

void Character::addStatus(Status* effect)
{
	statuses.push_back(effect);
	std::cout << name << " has the following status effects: \n";
	for (auto st : statuses)
	{
		std::cout << st->name << "\n";
	}
}

void Character::removeStatus(Status* effect)
{
	statuses.erase(std::remove(statuses.begin(), statuses.end(), effect), statuses.end());
	std::cout << name << " no longer has " << effect->name << " status.\n";
	delete(effect);
}

std::vector<std::string> Character::getStatuses()
{
	std::vector<std::string> statusNames;
	for (auto st : statuses)
		statusNames.push_back(st->name);
	return statusNames;
}

bool Character::hasStatus(std::string status)
{
	std::vector<std::string> statusnames = getStatuses();
	if (std::find(statusnames.begin(), statusnames.end(), status) != statusnames.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Character::statusTick(int phase)
{
	for (auto st : statuses)
	{
		switch (phase)
		{
		case 0: //turn start phase
			if (!skipTurn && st->skipProbability > 0)
			{
				if (st->skipProbability > randomizeInt(0, 100))
				{
					skipTurn = true;
					std::cout << name << " skipped turn due to " << st->name << " status.\n";
				}
			}
			break;
		case 1: //turn end phase
			if (st->damagePerTurn != 0)
			{
				std::cout << name << " took damage from " << st->name << ".\n";
				takeDamage(st->damagePerTurn, ignoreDef, this, Element::none);
			}
			st->duration--;
			if (st->duration == 0)
			{
				removeStatus(st);
			}
			break;
		case 2: //take damage phase
			defMultiplier *= st->defMultiplier;
			//std::cout << "physical damage multiplier is " << defMultiplier;
			mDefMultiplier *= st->mDefMultiplier;
			//std::cout << "magical damage multiplier is " << mDefMultiplier;
		default:
			break;
		}
	}
}
/*
void Character::applyStatus(Effect effect) 
{
	//if (condition != KO && condition != effect)
	if (condition == normal)
	{
		if (guarding)
		{
			std::cout << name << " avoided status by guarding. \n\n"; // TODO: don't block positive effects
		}
		else
		{
			if (effect == KO) {
				die();
			}
			else
			{
				condition = effect;
				if (effect == frozen || effect == burning) {
					statusTimer = 1;
				}
				else {
					statusTimer = 3; //apply status for 3 turns 
				}
				std::cout << name << " is now " << getStatusName() << ".\n\n";
			}
		}
	}
}
*/
/*
void Character::recoverStatus(bool revive) // temporary until status system is changed
{
	if (condition == KO && revive == false)
	{
		std::cout << name << "'s status can't be healed while dead.\n";
	}
	else if (condition == normal || condition == protect || condition == shell) // TODO: separate positive from negative effects
	{
		std::cout << name << "'s status is already normal.\n";
	}
	else
	{
		std::cout << name << "'s status is back to normal.\n";
		condition = normal;
		statusTimer = 0;
	}
}
*/

void Character::revive()
{
	if (condition == KO)
	{
		condition = normal;
		std::cout << name << " was revived.\n";
		if (currentHealth == 0) {
			currentHealth = 1;
		}
	}
}

void Character::clearStatuses(bool notify)
{
	if (statuses.size() > 0)
	{
		for (auto st : statuses)
		{
			delete(st);
		}
		statuses.clear();
		if (notify)
		{
			std::cout << name << "'s statuses were cleared!\n";
		}
	}
	else if (notify)
	{
		std::cout << name << " has no negative statuses.\n";
	}
}

void Character::guard() 
{
	guarding = true;
	counter = true;
	std::cout << name << " is guarding.\n\n";
}

void Character::takeDamage(int baseDamage, DamageType dmgType, Character* damager, Element elem)
{
	float damage = static_cast<float>(baseDamage); 
	// base damage is attack (+ possible crit), damage is base damage - defence
	if (dmgType == physical)
	{
		damage -= defence; // defence value is reduced from damage before applying status multipliers
	}
	else if (dmgType == magic)
	{
		damage -= magicDefence;
	}
	if (damage < 0)
	{
		damage = 0;
	}
	if (dmgType != ignoreDef)
	{
		if (guarding)
		{
			damage /= 2;
		}
		defMultiplier = 1.0f; // reset defence multipliers before re-calculating them
		mDefMultiplier = 1.0f;
		if (statuses.size() > 0)
		{
			statusTick(2); // apply multipliers from status effects
		}
		if (dmgType == physical)
		{
			damage *= defMultiplier;
		}
		if (dmgType == magic)
		{
			damage *= mDefMultiplier;
		}
	}
	if (weakness != Weakness::none && elem == static_cast<Element>(weakness))
	{
		damage *= 2;
		std::cout << "Double damage from weakness!\n";
	}

	currentHealth -= static_cast<int>(std::ceil(damage));
	std::cout << name << " took " << damage << " damage.\n";
	/*
	if (dmgType == physical && condition == sleep && randomizeInt(0, 1) == 1)
	{
		statusTimer = 0;
		condition = normal;
		std::cout << name << " woke up!\n";
	}
	if (condition == frozen && elem != Element::ice)
	{
		statusTimer = 0;
		condition = normal;
		std::cout << name << "'s ice melted!\n";
	}
	if (condition == burning && elem == Element::ice)
	{
		statusTimer = 0;
		condition = normal;
		std::cout << name << " is no longer burning!\n";
	}
	*/
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
		std::cout << name << " recovered to full HP.\n";
	} 
	else
	{
		std::cout << name << " recovered " << healAmount << " HP.\n\n";
	}
	//showStats();
}

void Character::recoverSP(int healAmount)
{
	currentSP += healAmount;
	if (currentSP >= maxSP)
	{
		currentSP = maxSP;
		std::cout << name << " recovered to full SP.\n\n";
	}
	else
	{
		std::cout << name << " recovered " << healAmount << " SP.\n\n";
	}
	//showStats();
}

void Character::EquipWeapon(Weapon* wpn) {
	delete(equippedWeapon);
	attack -= equippedWeapon->getAttack();
	equippedWeapon = wpn;
	attack += wpn->getAttack();
	std::cout << name << " equipped " << wpn->getName() << "\n\n";
}

void Character::unEquipWeapon() {
	delete(equippedWeapon);
	if (equippedWeapon != nullptr)
	{
		attack -= equippedWeapon->getAttack();
		equippedWeapon = new Weapon(Weapon::fists, 0, "Fists");
		std::cout << name << " unequipped weapon.\n\n";
	}
}

void Character::die()
{
	condition = KO;
	currentHealth = 0;
	//statusTimer = 0;
	for (auto st : statuses)
	{
		clearStatuses(false);
	}
	std::cout << name << " died.\n\n";
}

Character::~Character()
{
	delete(equippedWeapon);
	for (auto act : actions)
	{
		delete(act);
	}
	for (auto st : statuses)
	{
		delete(st);
	}
	//std::cout << name << " deleted.\n";
}