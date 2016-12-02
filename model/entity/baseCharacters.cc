#include <memory>
#include "baseCharacters.h"
#include "baseTreasure.h"
#include "entity.h"
#include "character.h"
#include "stats.h"
#include "../faction.h"
#include <cstdlib>
#include <math.h>

using namespace std;

Shade::Shade(): Character{1, Stats{25, 25, 0, 1.0, 0.5}, 125, 125} { }
Shade::~Shade() { }

int Shade::getScore() const {
	return getGold() * 1.5;
}

void Shade::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Shade>(shared_from_this()));
}

//VAMPIRE
Vampire::Vampire(): Character{1, Stats{25, 25, 0, 1.0, 0.5}, 50, -1} { }
Vampire::~Vampire() { }

void Vampire::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Vampire>(shared_from_this()));
}

//DROW
Drow::Drow(): Character{1, Stats{25, 15, 0, 1.5, 0.5}, 150, 150} { }
Drow::~Drow() { }

void Drow::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Drow>(shared_from_this()));
}

void Drow::getAttackedBy(shared_ptr<Elf> attacker) {
	takeDamage(attacker);
}

//GOBLIN
Goblin::Goblin(): Character{1, Stats{15, 20, 0, 1.0, 0.5}, 110, 110} { }
Goblin::~Goblin() { }

void Goblin::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Goblin>(shared_from_this()));
}

void Goblin::getAttackedBy(shared_ptr<Orc> attacker) {

	if (getStats().dodge * 100 > (rand() % 100)) {
		CharacterAttack msg {attacker, 
			static_pointer_cast<Character>(shared_from_this()), 0, true};
		notifyObservers(msg);
		return;
	}

	int attackerAtk = attacker->getStats().attack;
	int dmg = ceil(1.5 * (100.0 / ( 100.0+getStats().defence )) * attackerAtk);
	setHealth( getHealth() - dmg );

	CharacterAttack msg {attacker, 
		static_pointer_cast<Character>(shared_from_this()), dmg, false};
	notifyObservers(msg);
}

void Goblin::onKill() { 
	setGold(getGold() + 5);	// increase gold by 5 on kill
}

//TROLL
Troll::Troll(): Character{1, Stats{25, 15, 5, 1.0, 0.5}, 120, 120} { }
Troll::~Troll() { }

void Troll::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Troll>(shared_from_this()));
}

//DEFAULT ENEMY CHARACTERS
//HUMAN
Human::Human(): Character{2, Stats{20, 20, 0, 1.0, 0}, 140, 140} { }
Human::~Human() { }

vector<shared_ptr<Entity>> Human::onDeath() {
	vector<shared_ptr<Entity>> dropOnDeath;
	for (int i = 0 ; i < 2 ; i++) {	dropOnDeath.emplace_back(make_shared<NormalGold>()); } //add 2 normal gold piles
	return dropOnDeath;
}

void Human::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Human>(shared_from_this()));
}

//Dwarf
Dwarf::Dwarf(): Character{2, Stats{20, 30, 0, 1.0, 0}, 100, 100}  { }
Dwarf::~Dwarf() { }

void Dwarf::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Shade>(shared_from_this()));
}

void Dwarf::getAttackedBy(shared_ptr<Vampire> attacker) {
	if(takeDamage(attacker)) {
		attacker->setHealth( attacker->getHealth() - 5);	
	}
}

//Halfling
Halfling::Halfling(): Character{2, Stats{15, 20, 0, 1.0, 0.5}, 100, 100} { }
Halfling::~Halfling() { }

void Halfling::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Halfling>(shared_from_this()));
}

//Elf
Elf::Elf(): Character{2, Stats{30, 10, 0, 1.0, 0}, 140, 140} { }
Elf::~Elf() { }

void Elf::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Elf>(shared_from_this()));
}

//Orc
Orc::Orc(): Character{2, Stats{30, 25, 0, 1.0, 0}, 180, 180} { }
Orc::~Orc() { }

void Orc::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Orc>(shared_from_this()));
}

//Dragon
Dragon::Dragon(): Character{3, Stats{20, 20, 0, 1.0, 0}, 150, 150}, mHoard{} { }
Dragon::~Dragon() { }

void Dragon::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Dragon>(shared_from_this()));
}

shared_ptr<DragonHoard> Dragon::getHoard() const {
	return mHoard;
}

void Dragon::setHoard(shared_ptr<DragonHoard> hoard) {
	mHoard = hoard;
}

//Merchant
Merchant::Merchant(): Character{4, Stats{70, 5, 0, 1.0, 0}, 30, 30} { }
Merchant::~Merchant() { }

void Merchant::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Merchant>(shared_from_this()));
}

vector<shared_ptr<Entity>> Merchant::onDeath() {
	vector<shared_ptr<Entity>> dropOnDeath;
	// merchant hoard value 4 dropped
	dropOnDeath.emplace_back(make_shared<MerchantHoard>());
	return dropOnDeath;
}
