#include "stats.h"
#include "item.h"
#include "character.h"
#include "potion.h"
#include "entity.h"
#include "statsModifier.h"
#include <memory>

using namespace std;


Potion::Potion(Stats stats): mPotionStats(stats) { }

Potion::~Potion() { }


void Potion::itemUsedBy(shared_ptr<Character> character) {
	character = make_shared<StatsModifier>(character, mPotionStats);
}

void Potion::lookedOnBy(shared_ptr<Character>) {
	character->setKnowledgeOf(this, true);
}
