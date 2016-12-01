#ifndef MODIFIER_H
#define MODIFIER_H

#include "stats.h"
#include <memory>

class Modifier : public StatsContainer {

protected:
	std::shared_ptr<StatsContainer> mComponent;

public:
	Modifier(std::shared_ptr<StatsContainer>);
	virtual ~Modifier() = 0;

	virtual Stats getStats() = 0;
	virtual Stats getBaseStats() override;
};

#endif // MODIFIER_H
