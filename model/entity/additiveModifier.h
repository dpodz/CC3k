#ifndef ADDITIVE_MODIFIER_H
#define ADDITIVE__MODIFIER_H

#include "modifier.h"
#include "stats.h"
#include <vector>

class AdditiveModifier : public Modifier {

public:
	AdditiveModifier(std::shared_ptr<StatsContainer>, Stats);
	~AdditiveModifier();
	
	virtual Stats getStats() const override;
};

#endif // ADDITIVE_MODIFIER_H
