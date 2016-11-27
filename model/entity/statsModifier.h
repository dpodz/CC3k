#ifndef STATS_MODIFIER_H
#define STATS_MODIFIER_H

#include "modifier.h"
#include "stats.h"
#include "character.h"
#include <vector>

class StatsModifier : public Modifier {

	Stats mStatOffsets;

public:
	StatsModifier(std::shared_ptr<Character>, Stats);
	~StatsModifier();
	
	virtual Stats getStats() const override;
};

#endif // STATS_MODIFIER_H
