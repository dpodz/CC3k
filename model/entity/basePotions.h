#ifndef BASE_POTIONS_H
#define BASE_POTIONS_H

#include "potion.h"

class Character;

class BoostAtk: public Potion {
public:
	BoostAtk();
	~BoostAtk();
};

class WoundAtk: public Potion {
public:
	WoundAtk();
	~WoundAtk();
};

class BoostDef: public Potion {
public:
	BoostDef();
	~BoostDef();
};

class WoundDef: public Potion {
public:
	WoundDef();
	~WoundDef();
};

class RestoreHealth: public Potion {
public:
	RestoreHealth();
	~RestoreHealth();

	void itemUsedBy(std::shared_ptr<Character>) override;
};

class PoisonHealth: public Potion {
public:
	PoisonHealth();
	~PoisonHealth();

	void itemUsedBy(std::shared_ptr<Character>) override;
};




#endif // BASE_POTIONS_H
