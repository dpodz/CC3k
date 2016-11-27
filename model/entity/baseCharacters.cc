#include <memory>
#include "baseCharacters.h"
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

void Shade::lookedOnBy(shared_ptr<Character> character) {
	// TODO
}

void Shade::attack(shared_ptr<Entity> entity) {
	// TODO
}
