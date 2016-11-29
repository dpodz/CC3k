#ifndef BASE_TREASURE_H
#define BASE_TREASURE_H

#include "treasure.h"
#include <memory>

//forward declarations
class Dragon;

class MerchantHoard: public Treasure {
public:
	MerchantHoard();
	~MerchantHoard();
};

class SmallGold: public Treasure {
public:
	SmallGold();
	~SmallGold();
};

class NormalGold: public Treasure {
public:
	NormalGold();
	~NormalGold();
};

class DragonHoard: public Treasure {
	std::shared_ptr<Dragon> attachedDragon;
	
public:
	DragonHoard();
	~DragonHoard();
	
	void walkedOnBy(std::shared_ptr<Character>);
};

#endif // BASE_TREASURE_H
