#include "stats.h"
#include "item.h"
#include "character.h"
#include "potion.h"
#include "additiveModifier.h"
#include "../../messaging/messages.h"
#include "../../messaging/subject.h"
#include <memory>

using namespace std;


Potion::Potion(Stats stats): mPotionStats(stats) { }

Potion::~Potion() { }

void Potion::itemUsedBy(shared_ptr<Character> character) {	

	auto self = static_pointer_cast<Potion>(shared_from_this());

	character->setStatsContainer(make_shared<AdditiveModifier>
		(character->getStatsContainer(), mPotionStats));
	character->setKnowledgeOf(self, true);

	ItemUsed msg {character, self};
	notifyObservers(msg);
}
