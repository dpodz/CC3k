#ifndef TREASURE_H
#define TREASURE_H

#include "item.h"
#include <memory>

class Character;

class Treasure : public Item {

public:
	Treasure(int);
	~Treasure();
	
	virtual void walkedOnBy(std::shared_ptr<Character>) override;
	virtual bool canWalkOn() override;
};

#endif // TREASURE_H
