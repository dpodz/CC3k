#include "modifier.h"
#include "additiveModifier.h"
#include "stats.h"
#include <vector>
#include <memory>
#include <math.h>

using namespace std;


AdditiveModifier::AdditiveModifier(shared_ptr<StatsContainer> statsContainer, Stats stats): 
				Modifier{statsContainer, stats} { }

AdditiveModifier::~AdditiveModifier() { }

Stats AdditiveModifier::getStats() const {
	Stats charStats = mComponent->getStats();

	Stats newStats{max(0, charStats.attack + (int)ceil(mStats.attack * charStats.potionStrength)), 
		max(0, charStats.defence + (int)ceil(mStats.defence * charStats.potionStrength)), 
		charStats.healthRegen + (int)ceil(mStats.healthRegen * charStats.potionStrength),
		max(0.0, charStats.potionStrength + mStats.potionStrength * charStats.potionStrength)};

	return newStats;
}
