#include "stats.h"
#include "item.h"
#include "character.h"
#include "potion.h"
#include "entity.h"
#include "modifier.h"
#include "statsModifier.h"
#include <memory>

using namespace std;


Potion::Potion(Stats stats): mPotionStats(stats) { }

Potion::~Potion() { }

// TODO: Fix this using messaging
void Potion::itemUsedBy(shared_ptr<Character> character) {	
//	StatsModifier statMod{character,mPotionStats};
	character = make_shared<StatsModifier>(character,mPotionStats);
}

void Potion::lookedOnBy(shared_ptr<Character> character) {
	character->setKnowledgeOf(shared_ptr<Potion>(this), true);
}
