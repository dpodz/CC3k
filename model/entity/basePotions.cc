#include "basePotions.h"
#include "item.h"
#include "potion.h"
#include "stats.h"
#include "character.h"

using namespace std;

BoostAtk::BoostAtk(): Potion {Stats{5,0,0,0}} {}

BoostAtk::~BoostAtk() {}

WoundAtk::WoundAtk(): Potion {Stats{-5,0,0,0}} {}

WoundAtk::~WoundAtk() {}

BoostDef::BoostDef() : Potion {Stats{0,5,0,0}} {}

BoostDef::~BoostDef() {}

WoundDef::WoundDef() : Potion {Stats{0,-5,0,0}} {}

WoundDef::~WoundDef() {}

RestoreHealth::RestoreHealth(): Potion {Stats{0,0,0,0}} {}

RestoreHealth::~RestoreHealth() {}

void RestoreHealth::itemUsedBy(shared_ptr<Character> character) {
	character->setHealth(character->getHealth() + 10);
}

PoisonHealth::PoisonHealth(): Potion {Stats{0,0,0,0}} {}

PoisonHealth::~PoisonHealth() {}

void PoisonHealth::itemUsedBy(shared_ptr<Character> character) {
	character->setHealth(character->getHealth() - 10);
}
