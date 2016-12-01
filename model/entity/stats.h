#ifndef STATS_H
#define STATS_H

struct Stats {
	int attack;
	int defence;
	int healthRegen;
	double potionStrength;
};

class StatsContainer {

protected:
	Stats mStats;

public: 

	StatsContainer(Stats);
	~StatsContainer();

	virtual Stats getStats() const;
	virtual Stats getBaseStats() const;
};

#endif // STATS_H
