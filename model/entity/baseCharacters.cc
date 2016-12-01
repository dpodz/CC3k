#include <memory>
#include "baseCharacters.h"
#include "baseTreasure.h"
#include "entity.h"
#include "character.h"
#include "stats.h"
#include "../faction.h"

using namespace std;

Shade::Shade(): Character{1, Stats{25, 25, 0, 1.0}, 125, 125} { }
Shade::~Shade() { }

int Shade::getScore() const {
	return getGold() * 1.5;
}

void Shade::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Shade>(shared_from_this()), this->getStats().attack);
}

//VAMPIRE
Vampire::Vampire(): Character{1, Stats{25, 25, 0, 1.0}, 50, 50} { }
Vampire::~Vampire() { }

void Vampire::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Vampire>(shared_from_this()), this->getStats().attack);
	// restore health, unless attacking a dwarf
	int healthSteal = 5;
	if (typeid(defender) == typeid(Dwarf)) {
		healthSteal = -5;
	}
	this->setHealth( this->getHealth() + healthSteal );	
}

//DROW
Drow::Drow(): Character{1, Stats{25, 15, 0, 1.5	}, 150, 150} { }
Drow::~Drow() { }

void Drow::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Drow>(shared_from_this()), this->getStats().attack);
}

//GOBLIN
Goblin::Goblin(): Character{1, Stats{15, 20, 0, 1.0}, 110, 110} { }
Goblin::~Goblin() { }

void Goblin::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Goblin>(shared_from_this()), this->getStats().attack);
}

void Goblin::getAttackedBy(shared_ptr<Orc> attacker, int attackDamage) {
	this->takeDamage(attackDamage * 1.5); // take extra damage from Orcs
}

void Goblin::onKill() { 
	this->setHealth(getHealth() + 5);	// increase gold by 5 on kill
}

//TROLL
Troll::Troll(): Character{1, Stats{25, 15, 5, 1.0}, 120, 120} { }
Troll::~Troll() { }

void Troll::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Troll>(shared_from_this()), this->getStats().attack);
}

//DEFAULT ENEMY CHARACTERS
//HUMAN
Human::Human(): Character{2, Stats{20, 20, 0, 1.0}, 140, 140} { }
Human::~Human() { }

vector<shared_ptr<Entity>> Human::onDeath() {
	vector<shared_ptr<Entity>> dropOnDeath;
	for (int i = 0 ; i < 2 ; i++) {	dropOnDeath.emplace_back(make_shared<NormalGold>()); } //add 2 normal gold piles
	return dropOnDeath;
}

void Human::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Human>(shared_from_this()), this->getStats().attack);
}

//Dwarf
Dwarf::Dwarf(): Character{2, Stats{20, 30, 0, 1.0}, 100, 100}  { }
Dwarf::~Dwarf() { }

void Dwarf::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Shade>(shared_from_this()), this->getStats().attack);
}

//Halfling
Halfling::Halfling(): Character{2, Stats{15, 20, 0, 1.0}, 100, 100} { }
Halfling::~Halfling() { }

void Halfling::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Halfling>(shared_from_this()), this->getStats().attack);
}

//Elf
Elf::Elf(): Character{2, Stats{30, 10, 0, 1.0}, 140, 140} { }
Elf::~Elf() { }

void Elf::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	int numAttacks = 2;
	if (typeid(defender) == typeid(Drow)) { numAttacks = 1; }
	for (int i = 0 ; i < numAttacks ; i++) {
		defender->getAttackedBy(static_pointer_cast<Elf>(shared_from_this()), this->getStats().attack);
	}
}

//Orc
Orc::Orc(): Character{2, Stats{30, 25, 0, 1.0}, 180, 180} { }
Orc::~Orc() { }

void Orc::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Orc>(shared_from_this()), this->getStats().attack);
}

//Dragon
Dragon::Dragon(): Character{3, Stats{20, 20, 0, 1.0}, 150, 150} { }
Dragon::~Dragon() { }

void Dragon::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Dragon>(shared_from_this()), this->getStats().attack);
}

//Merchant
Merchant::Merchant(): Character{4, Stats{70, 5, 0, 1.0}, 30, 30} { }
Merchant::~Merchant() { }

void Merchant::attack(shared_ptr<Character> defender) {
	// send the character and its attack value to the enemy
	defender->getAttackedBy(static_pointer_cast<Merchant>(shared_from_this()), this->getStats().attack);
}

vector<shared_ptr<Entity>> Merchant::onDeath() {
	vector<shared_ptr<Entity>> dropOnDeath;
	// merchant hoard value 4 dropped
	dropOnDeath.emplace_back(make_shared<MerchantHoard>());
	return dropOnDeath;
}
