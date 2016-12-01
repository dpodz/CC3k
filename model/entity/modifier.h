#ifndef MODIFIER_H
#define MODIFIER_H

#include "stats.h"
#include <memory>

class Modifier : public StatsContainer {

protected:
	std::shared_ptr<StatsContainer> mComponent;

public:
	Modifier(std::shared_ptr<StatsContainer>, Stats);
	virtual ~Modifier() = 0;

	virtual Stats getStats() const = 0;
	virtual Stats getBaseStats() const override;
};

#endif // MODIFIER_H
