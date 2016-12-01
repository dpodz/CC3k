#include "stats.h"

StatsContainer::StatsContainer(Stats stats): mStats(stats) {}

StatsContainer::~StatsContainer() { }

Stats StatsContainer::getStats() const {
	return mStats;
}

Stats StatsContainer::getBaseStats() const {
	return mStats;
}
