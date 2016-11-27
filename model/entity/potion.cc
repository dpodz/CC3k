#include "stats.h"
#include "item.h"
#include "character.h"
#include "potion.h"
#include "entity.h"
#include <memory>

using namespace std;


Potion::Potion(Stats stats): mPotionStats{stats} { }

Potion::~Potion() { }


void Potion::itemUsedBy(shared_ptr<Character> character) {
	// TODO: when Modifier is done	
}

bool Potion::canWalkOn() { return false; }

void Potion::lookedOnBy(shared_ptr<Character>) {
	// TODO
}
