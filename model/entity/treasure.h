#ifndef TREASURE_H
#define TREASURE_H

#include "item.h"
#include "character.h"
#include <memory>

class Treasure : public Item {

public:
	Treasure(int);
	~Treasure();
	
	virtual void walkedOnBy(std::shared_ptr<Character>) override;
};

#endif // TREASURE_H
