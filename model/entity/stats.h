#ifndef STATS_H
#define STATS_H

class StatsContainer {
	Stats mStats;

public: 

	StatsContainer(Stats);
	~StatsContainer();

	virtual Stats getStats();
	virtual Stats getBaseStats();
}

struct Stats {
	int attack;
	int defence;
	int healthRegen;
	double potionStrength;
};

#endif // STATS_H
