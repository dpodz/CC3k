#include "poisonHealth.h"
#include "item.h"
#include "potion.h"
#include "stats.h"
#include "character.h"

using namespace std;

PoisonHealth::PoisonHealth(): Potion{Stats{0,0,0,0}} { }

PoisonHealth::~PoisonHealth() { }

void PoisonHealth::itemUsedBy(shared_ptr<Character> character) {
        character->setHealth(character->getHealth() - 10);
}
