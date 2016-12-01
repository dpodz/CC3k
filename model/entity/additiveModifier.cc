#include "modifier.h"
#include "additiveModifier.h"
#include "stats.h"
#include <vector>
#include <memory>

using namespace std;


AdditiveModifier::AdditiveModifier(shared_ptr<StatsContainer> statsContainer, Stats stats): 
				Modifier{statsContainer, stats} { }

AdditiveModifier::~AdditiveModifier() { }


Stats AdditiveModifier::getStats() const {
	Stats charStats = mComponent->getStats();

	Stats newStats{charStats.attack + mStats.attack, 
		charStats.defence + mStats.defence, 
		charStats.healthRegen + mStats.healthRegen,
		charStats.potionStrength + mStats.potionStrength};

	return newStats;
}
