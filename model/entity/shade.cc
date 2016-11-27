#include <memory>
#include "shade.h"
#include "entity.h"
#include "character.h"
#include "stats.h"
#include "../faction.h"


Shade::Shade(): Character{1, Stats{25, 25, 0, 1.0}, 125, 125} { }

Shade::~Shade() { }

int Shade::getScore() const {
	return getGold() * 1.5;
}

bool Shade::canWalkOn() {
	return false;
}

void Shade::lookedOnBy(std::shared_ptr<Character> character) {
	// TODO
}

void Shade::attack(std::shared_ptr<Entity> entity) {
	// TODO
} 
