#include "basePotions.h"
#include "item.h"
#include "potion.h"
#include "stats.h"
#include "character.h"
#include <math.h>

using namespace std;

BoostAtk::BoostAtk(): Potion {Stats{5,0,0,0,0}} {}

BoostAtk::~BoostAtk() {}

WoundAtk::WoundAtk(): Potion {Stats{-5,0,0,0,0}} {}

WoundAtk::~WoundAtk() {}

BoostDef::BoostDef() : Potion {Stats{0,5,0,0,0}} {}

BoostDef::~BoostDef() {}

WoundDef::WoundDef() : Potion {Stats{0,-5,0,0,0}} {}

WoundDef::~WoundDef() {}

RestoreHealth::RestoreHealth(): Potion {Stats{0,0,0,0,0}} {}

RestoreHealth::~RestoreHealth() {}

void RestoreHealth::itemUsedBy(shared_ptr<Character> character) {
	auto self = static_pointer_cast<Potion>(shared_from_this());

	character->setHealth(character->getHealth() + ceil(10 * character->getStats().potionStrength));
	character->setKnowledgeOf(self, true);

	ItemUsed msg {character, self};
	notifyObservers(msg);
}

PoisonHealth::PoisonHealth(): Potion {Stats{0,0,0,0,0}} {}

PoisonHealth::~PoisonHealth() {}

void PoisonHealth::itemUsedBy(shared_ptr<Character> character) {
	auto self = static_pointer_cast<Potion>(shared_from_this());

	character->setHealth(character->getHealth() - ceil(10 * character->getStats().potionStrength));
	character->setKnowledgeOf(self, true);

	ItemUsed msg {character, self};
	notifyObservers(msg);
}
