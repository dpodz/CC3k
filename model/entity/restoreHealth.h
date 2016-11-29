#ifndef RESTOREHEALTH_H
#define RESTOREHEALTH_H

#include "stats.h"
#include "potion.h"

class RestoreHealth: public Potion {
public:
	RestoreHealth();
	~RestoreHealth();

	void itemUsedBy(std::shared_ptr<Character>) override;
};

#endif
