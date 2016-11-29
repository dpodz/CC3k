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

//VAMPIRE
Vampire::Vampire(): Character{1, Stats{25, 25, 0, 1.0}, 50, 50} { }
Vampire::~Vampire() { }

//TODO
void Vampire::attack(std::shared_ptr<Entity> entity) { }

//DROW
Drow::Drow(): Character{1, Stats{25, 15, 0, 1.5	}, 150, 150} { }
Drow::~Drow() { }

//GOBLIN
Goblin::Goblin(): Character{1, Stats{15, 20, 0, 1.0}, 110, 110} { }
Goblin::~Goblin() { }

//TODO
void Goblin::onKill() { }

//TROLL
Troll::Troll(): Character{1, Stats{25, 15, 5, 1.0}, 120, 120} { }
Troll::~Troll() { }

//DEFAULT ENEMY CHARACTERS
//HUMAN
Human::Human(): Character{2, Stats{20, 20, 0, 1.0}, 140, 140} { }
Human::~Human() { }

vector<shared_ptr<Entity>> Human::onDeath() {
	vector<shared_ptr<Entity>> dropOnDeath;
	for (int i = 0 ; i < 2 ; i++) {	dropOnDeath.emplace_back(make_shared<NormalGold>()); } //add 2 normal gold piles
	return dropOnDeath;
}

//Dwarf
Dwarf::Dwarf(): Character{2, Stats{20, 30, 0, 1.0}, 100, 100}  { }
Dwarf::~Dwarf() { }

//Halfling
Halfling::Halfling(): Character{2, Stats{15, 20, 0, 1.0}, 100, 100} { }
Halfling::~Halfling() { }

// TODO
void Halfling::getAttackedBy(shared_ptr<Entity> entity) { }

//Elf
Elf::Elf(): Character{2, Stats{30, 10, 0, 1.0}, 140, 140} { }
Elf::~Elf() { }

//TODO
void Elf::attack(shared_ptr<Entity> entity) { }

//Orc
Orc::Orc(): Character{2, Stats{30, 25, 0, 1.0}, 180, 180} { }
Orc::~Orc() { }

//TODO
void Orc::attack(shared_ptr<Entity> entity) { }

//Dragon
Dragon::Dragon(): Character{3, Stats{20, 20, 0, 1.0}, 150, 150} { }
Dragon::~Dragon() { }

//Merchant
Merchant::Merchant(): Character{4, Stats{70, 5, 0, 1.0}, 30, 30} { }
Merchant::~Merchant() { }


vector<shared_ptr<Entity>> Merchant::onDeath() {
	vector<shared_ptr<Entity>> dropOnDeath;
	// merchant hoard value 4 dropped
	dropOnDeath.emplace_back(make_shared<MerchantHoard>());
	return dropOnDeath;
}
