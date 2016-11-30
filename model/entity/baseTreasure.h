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
	std::weak_ptr<Dragon> attachedDragon;
	
public:
	DragonHoard();
	~DragonHoard();
	
	void setDragon(std::shared_ptr<Dragon>);
	virtual void walkedOnBy(std::shared_ptr<Character>) override;
};

#endif // BASE_TREASURE_H
