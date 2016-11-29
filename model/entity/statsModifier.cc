#include "modifier.h"
#include "statsModifier.h"
#include "stats.h"
#include <vector>
#include <memory>

using namespace std;


StatsModifier::StatsModifier(shared_ptr<Character> character, Stats stats): 
				Modifier{character}, mStatOffsets(stats) { }

StatsModifier::~StatsModifier() { }


Stats StatsModifier::getStats() const {
	Stats charStats = mComponent->getStats();

	Stats newStats{charStats.attack + mStatOffsets.attack, 
		charStats.defence + mStatOffsets.defence, 
		charStats.healthRegen + mStatOffsets.healthRegen,
		charStats.potionStrength + mStatOffsets.potionStrength};

	return newStats;
}
