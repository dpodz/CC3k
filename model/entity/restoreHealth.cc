#include "restoreHealth.h"
#include "item.h"
#include "potion.h"
#include "stats.h"
#include "character.h"

using namespace std;

RestoreHealth::RestoreHealth(): Potion{Stats{0,0,0,0}} { }

RestoreHealth::~RestoreHealth() { }

void RestoreHealth::itemUsedBy(shared_ptr<Character> character) {
	character->setHealth(character->getHealth() + 10);
}
