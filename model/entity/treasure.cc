#include "stats.h"
#include "item.h"
#include "treasure.h"
#include "character.h"
#include <memory>

using namespace std;

Treasure::Treasure(int value) { 
	setGold(value);
}

Treasure::~Treasure() { }

void Treasure::walkedOnBy(shared_ptr<Character> character) {

	character->setGold(character->getGold() + getGold());

	ItemPickedUp msg {character, 
		static_pointer_cast<Item>(shared_from_this())};
	notifyObservers(msg);
}

bool Treasure::canWalkOn() {
	return true;
}
