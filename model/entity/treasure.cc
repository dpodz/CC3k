#include "stats.h"
#include "item.h"
#include "treasure.h"
#include "character.h"
#include <memory>

using namespace std;

Treasure::Treasure(int value) { 
	this->setGold(value);
}

Treasure::~Treasure() { }

bool Treasure::canWalkOn() {
	return true;
}

void Treasure::lookedOnBy(shared_ptr<Character>) {
	// TODO
}

void Treasure::walkedOnBy(shared_ptr<Character> character) {
	// TODO
}
