#include "modifier.h"
#include "additiveModifier.h"
#include "stats.h"
#include <vector>
#include <memory>

using namespace std;


AdditiveModifier::AdditiveModifier(shared_ptr<StatsContainer> statsContainer, Stats stats): 
				Modifier{statsContainer}, mStatOffsets(stats) { }

AdditiveModifier::~AdditiveModifier() { }


Stats AdditiveModifier::getStats() const {
	Stats charStats = mComponent->getStats();

	Stats newStats{charStats.attack + mStatOffsets.attack, 
		charStats.defence + mStatOffsets.defence, 
		charStats.healthRegen + mStatOffsets.healthRegen,
		charStats.potionStrength + mStatOffsets.potionStrength};

	return newStats;
}
