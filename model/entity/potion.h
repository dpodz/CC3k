#ifndef POTION_H
#define POTION_H

#include "stats.h"
#include "item.h"
#include <memory>

class Character;
class Potion : public Item {

	Stats mPotionStats;

public:
	Potion(Stats);
	~Potion();
		
	virtual void itemUsedBy(std::shared_ptr<Character>) override;
};

#endif // POTION_H
