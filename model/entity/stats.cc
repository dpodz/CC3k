#include "stats.h"

StatsContainer::StatsContainer(Stats stats): mStats(stats) {}

StatsContainer::~StatsContainer() { }

Stats StatsContainer::getStats() {
	return mStats;
}

Stats StatsContainer::getBaseStats() {
	return mStats;
}
